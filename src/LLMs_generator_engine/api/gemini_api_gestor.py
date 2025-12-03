#!/usr/bin/env python3
import os
import re
import sys
import json
import time
import requests
from pathlib import Path
from typing import Union, Dict, Optional
from datetime import datetime, timedelta
from dotenv import load_dotenv

import google.generativeai as genai

# Aggiungi la directory parent (src) al path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), "../.."))

from utility_dir import utility_paths
from utility_dir import prompt_generator


class ApiKeyCache:
    """Gestisce la cache delle API key con timestamp di disponibilità"""

    def __init__(self, cache_file: Path):
        self.cache_file = cache_file
        self.cache: Dict[str, dict] = {}
        self._load_cache()

    def _load_cache(self):
        """Carica la cache da file JSON"""
        if self.cache_file.exists():
            try:
                with open(self.cache_file, 'r') as f:
                    data = json.load(f)
                    # Converti timestamp string a datetime
                    for key, info in data.items():
                        if info.get('available_at'):
                            info['available_at'] = datetime.fromisoformat(info['available_at'])
                    self.cache = data
                print(f"📂 Cache caricata da {self.cache_file}")
            except Exception as e:
                print(f"⚠️ Errore caricamento cache: {e}")
                self.cache = {}
        else:
            print("📂 Nessuna cache esistente, creazione nuova")
            self.cache = {}

    def _save_cache(self):
        """Salva la cache su file JSON"""
        try:
            # Converti datetime a string per JSON
            serializable_cache = {}
            for key, info in self.cache.items():
                info_copy = info.copy()
                if info_copy.get('available_at') and isinstance(info_copy['available_at'], datetime):
                    info_copy['available_at'] = info_copy['available_at'].isoformat()
                serializable_cache[key] = info_copy

            self.cache_file.parent.mkdir(parents=True, exist_ok=True)
            with open(self.cache_file, 'w') as f:
                json.dump(serializable_cache, f, indent=2)
            print(f"💾 Cache salvata in {self.cache_file}")
        except Exception as e:
            print(f"❌ Errore salvataggio cache: {e}")

    def add_key(self, api_key: str):
        """Aggiunge una nuova key alla cache (se non esiste)"""
        key_id = api_key[:12]  # Usa i primi 12 caratteri come ID
        if key_id not in self.cache:
            self.cache[key_id] = {
                'full_key': api_key,
                'available': True,
                'available_at': None,
                'total_429_errors': 0,
                'last_error': None
            }
            self._save_cache()

    def mark_unavailable(self, api_key: str, retry_delay_seconds: float):
        """Marca una key come non disponibile per un certo periodo"""
        key_id = api_key[:12]
        if key_id in self.cache:
            available_at = datetime.now() + timedelta(seconds=retry_delay_seconds)
            self.cache[key_id]['available'] = False
            self.cache[key_id]['available_at'] = available_at
            self.cache[key_id]['total_429_errors'] += 1
            self.cache[key_id]['last_error'] = datetime.now().isoformat()
            self._save_cache()
            print(f"⏰ Key {key_id}... non disponibile fino a {available_at.strftime('%H:%M:%S')}")

    def remove_key(self, api_key: str, reason: str):
        """Rimuove definitivamente una key dalla cache"""
        key_id = api_key[:12]
        if key_id in self.cache:
            print(f"🗑️ Rimossa key {key_id}... dalla cache (motivo: {reason})")
            del self.cache[key_id]
            self._save_cache()

    def get_next_available_key(self) -> Optional[tuple]:
        """
        Restituisce la prossima key disponibile.
        Ritorna: (api_key, wait_time_seconds) o None se cache vuota
        """
        if not self.cache:
            return None

        now = datetime.now()

        # Prima cerca key immediatamente disponibili
        for key_id, info in self.cache.items():
            if info['available']:
                return (info['full_key'], 0.0)

            # Se ha available_at, controlla se è passato il tempo
            if info.get('available_at') and isinstance(info['available_at'], datetime):
                if now >= info['available_at']:
                    # Riattiva la key
                    info['available'] = True
                    info['available_at'] = None
                    self._save_cache()
                    print(f"✅ Key {key_id}... riattivata")
                    return (info['full_key'], 0.0)

        # Nessuna key disponibile immediatamente, trova quella con wait minore
        min_wait = None
        best_key = None

        for key_id, info in self.cache.items():
            if info.get('available_at') and isinstance(info['available_at'], datetime):
                wait_seconds = (info['available_at'] - now).total_seconds()
                if wait_seconds > 0:
                    if min_wait is None or wait_seconds < min_wait:
                        min_wait = wait_seconds
                        best_key = info['full_key']

        if best_key:
            return (best_key, min_wait)

        return None

    def is_empty(self) -> bool:
        """Verifica se la cache è vuota"""
        return len(self.cache) == 0

    def get_status(self) -> str:
        """Restituisce lo stato della cache per debugging"""
        if not self.cache:
            return "Cache vuota"

        now = datetime.now()
        status_lines = [f"Cache con {len(self.cache)} key:"]

        for key_id, info in self.cache.items():
            if info['available']:
                status_lines.append(f"  ✅ {key_id}... - Disponibile")
            elif info.get('available_at') and isinstance(info['available_at'], datetime):
                wait = (info['available_at'] - now).total_seconds()
                if wait > 0:
                    status_lines.append(f"  ⏰ {key_id}... - Disponibile tra {wait:.0f}s")
                else:
                    status_lines.append(f"  🔄 {key_id}... - Pronta per riattivazione")
            else:
                status_lines.append(f"  ❓ {key_id}... - Stato sconosciuto")

        return "\n".join(status_lines)


class GeminiAIApiGestor:
    def __init__(self):
        self.llm_config_json_file_path = (
            utility_paths.SRC_DIR / "LLMs_generator_engine" / "llm_configs.json"
        )

        # Percorso cache
        cache_dir = utility_paths.SRC_DIR / "LLMs_generator_engine" / "api"
        self.cache_file = cache_dir / ".gemini_key_cache.json"

        load_dotenv()
        api_keys_raw = os.getenv("GEMINI_API_KEYS")
        if not api_keys_raw:
            raise ValueError("❌ GEMINI_API_KEYS non trovato nel file .env")

        try:
            api_keys_list = json.loads(api_keys_raw)
            if not isinstance(api_keys_list, list):
                raise ValueError("GEMINI_API_KEYS deve essere un array JSON.")
        except Exception as e:
            raise ValueError(f"❌ Errore parsing GEMINI_API_KEYS: {e}")

        # Inizializza la cache
        self.key_cache = ApiKeyCache(self.cache_file)

        # Aggiungi tutte le key alla cache
        for key in api_keys_list:
            self.key_cache.add_key(key)

        if self.key_cache.is_empty():
            raise RuntimeError("❌ Nessuna API key valida disponibile nella cache!")

        self.webhook_url = os.getenv("DISCORD_WEBHOOK")  # opzionale
        self.api_key = None
        self.model = None

        # Config generazione
        try:
            with open(self.llm_config_json_file_path, "r", encoding="utf-8") as f:
                content = json.load(f)
                if "gemini" not in content:
                    raise Exception(f"'gemini' non trovato in config file:\n{content}")
                self.gemini_config = content["gemini"]
        except Exception as e:
            print(f"⚠️ Errore caricamento configurazione Gemini:\n{e}")
            self.gemini_config = {"temperature": 0.3, "max_output_tokens": 8000}

        # Imposta la prima key valida
        if not self._set_next_key():
            msg = "❌ Nessuna API key valida disponibile."
            print(msg)
            self._send_webhook(msg)
            raise RuntimeError(msg)

    def _send_webhook(self, message: str):
        if not self.webhook_url:
            return
        try:
            requests.post(self.webhook_url, json={"text": message}, timeout=5)
            print("📡 Webhook inviato.")
        except Exception as e:
            print(f"❌ Errore invio webhook: {e}")

    def _set_next_key(self) -> bool:
        """
        Ottiene la prossima API key disponibile dalla cache.
        Ritorna False se la cache è vuota.
        """
        result = self.key_cache.get_next_available_key()

        if result is None:
            print("❌ Cache vuota! Nessuna key disponibile.")
            self._send_webhook("🚨 PROBLEMA GRAVE: Cache API key vuota!")
            return False

        api_key, wait_time = result

        if wait_time > 0:
            print(f"⏳ Nessuna key immediatamente disponibile, attendo {wait_time:.1f}s...")
            time.sleep(wait_time)
            # Dopo l'attesa, riprova
            return self._set_next_key()

        self.api_key = api_key

        try:
            genai.configure(api_key=self.api_key)
            self.model = genai.GenerativeModel("gemini-2.0-flash")
            print(f"✅ Impostata API key {self.api_key[:12]}...")
            return True
        except Exception as e:
            print(f"❌ Errore configurazione key {self.api_key[:12]}... -> {e}")
            # Rimuovi key non valida
            self.key_cache.remove_key(self.api_key, f"Errore configurazione: {e}")
            return self._set_next_key()

    def _handle_api_error(self, error: Exception) -> bool:
        """
        Gestisce gli errori API e decide se rotare la key.
        Ritorna True se può continuare con una nuova key, False altrimenti.
        """
        error_str = str(error)

        # Estrai retry_delay da errori 429
        retry_delay = 60.0  # Default 60 secondi
        retry_match = re.search(r'retry in (\d+(?:\.\d+)?)s', error_str, re.IGNORECASE)
        if retry_match:
            retry_delay = float(retry_match.group(1))

        # Controlla se è un errore 429 (quota exceeded)
        if '429' in error_str or 'quota' in error_str.lower() or 'rate limit' in error_str.lower():
            print(f"⚠️ Errore 429 - Quota superata, key non disponibile per {retry_delay}s")
            self.key_cache.mark_unavailable(self.api_key, retry_delay)
            return self._set_next_key()

        # Controlla errori gravi (400, 403, 404, leaked key, etc.)
        severe_error_patterns = [
            '400', '403', '404',
            'leaked', 'invalid', 'disabled', 'revoked',
            'api key not valid', 'authentication failed'
        ]

        if any(pattern in error_str.lower() for pattern in severe_error_patterns):
            reason = "Errore grave (key leaked/invalida/revocata)"
            print(f"🚫 {reason}: {error_str[:100]}")
            self.key_cache.remove_key(self.api_key, reason)
            self._send_webhook(f"⚠️ Key rimossa: {self.api_key[:12]}... - {reason}")
            return self._set_next_key()

        # Altri errori (network, timeout, etc.) - prova key successiva
        print(f"⚠️ Errore generico, provo key successiva: {error_str[:100]}")
        return self._set_next_key()

    def _clean_markdown(self, generated_code: str) -> str:
        if "```" in generated_code:
            lines = generated_code.split("\n")
            clean_lines = []
            in_code_block = False
            for line in lines:
                if line.strip().startswith("```"):
                    in_code_block = not in_code_block
                    continue
                if in_code_block or not line.strip().startswith("```"):
                    clean_lines.append(line)
            return "\n".join(clean_lines).strip()
        return generated_code

    def make_api_call(self, prompt: str, max_retries: int = None) -> Union[str, None]:
        """
        Prova chiamata API, se fallisce gestisce l'errore e riprova con un'altra key.

        Args:
            prompt: Il prompt da inviare
            max_retries: Numero massimo di tentativi (None = illimitato finché ci sono key)
        """
        attempt = 0

        while True:
            if max_retries is not None and attempt >= max_retries:
                print(f"❌ Raggiunto limite massimo di {max_retries} tentativi")
                return None

            if self.key_cache.is_empty():
                msg = "🚨 PROBLEMA GRAVE: Cache completamente vuota! Nessuna key disponibile."
                print(msg)
                self._send_webhook(msg)
                return None

            try:
                print(f"🔄 Tentativo {attempt + 1} con key {self.api_key[:12]}...")
                response = self.model.generate_content(
                    prompt, generation_config=self.gemini_config
                )
                print(f"✅ Risposta ricevuta con successo")
                return self._clean_markdown(response.text.strip())

            except Exception as e:
                print(f"❌ Errore API con key {self.api_key[:12]}... -> {e}")

                # Gestisci l'errore e decidi se continuare
                if not self._handle_api_error(e):
                    return None

                attempt += 1

                # Mostra stato cache ogni 3 tentativi
                if attempt % 3 == 0:
                    print(self.key_cache.get_status())

    def generate_and_save_LLM_code_by_files(
        self,
        prompt_file_path: Path,
        base_snippet_code_file_path: Path,
        exercise_dir_file_path: Path,
        prompt_version_number: int,
        exercise_name: str,
    ) -> bool:
        try:
            file_ext = os.path.splitext(base_snippet_code_file_path)[1].lstrip(".")
        except IndexError:
            print("❌ Errore: impossibile determinare estensione file.")
            return False

        e_name = (exercise_name.split("."))[0]
        file_name = f"GeminiFlash_{e_name}_v{prompt_version_number}.{file_ext}"
        gemini_dir = exercise_dir_file_path / "gemini"
        output_file_path = gemini_dir / file_name

        if os.path.exists(str(output_file_path)):
            print(f"-> file {output_file_path} già esistente, skip generation")
            return True

        final_prompt = prompt_generator.create_api_prompt_from_files(
            prompt_file_path, base_snippet_code_file_path
        )
        if not final_prompt:
            print("❌ Errore generazione prompt.")
            return False

        generated_code = self.make_api_call(final_prompt)
        if generated_code is None:
            print("❌ Nessun codice generato.")
            return False

        # Estrai blocco di codice da markdown se presente
        code_match = re.search(r"```(?:\w+)?\n(.*?)```", generated_code, re.DOTALL)
        extracted_code = (
            code_match.group(1).strip() if code_match else generated_code.strip()
        )

        try:
            os.makedirs(gemini_dir, exist_ok=True)
            with open(output_file_path, "w", encoding="utf-8") as f:
                f.write(extracted_code)

            print(f"✅ (gemini) Codice salvato in: {output_file_path}")
            return True
        except Exception as e:
            print(f"❌ Errore salvataggio file: {e}")
            return False




if __name__ == "__main__":
    gestor = GeminiAIApiGestor()
    print("\n" + gestor.key_cache.get_status())
    print("\n" + "="*60)
    print("Test chiamata API:")
    result = gestor.make_api_call("Hi Gemini, quick dynamic key rotation test :)")
    print(f"\nRisposta: {result[:100] if result else 'None'}...")
    print("\n" + gestor.key_cache.get_status())
