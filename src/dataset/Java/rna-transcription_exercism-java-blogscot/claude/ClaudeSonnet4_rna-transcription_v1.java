class RnaTranscription {

  private static final char[] TRANSCRIPTION_MAP = new char[256];
  
  static {
    TRANSCRIPTION_MAP['C'] = 'G';
    TRANSCRIPTION_MAP['G'] = 'C';
    TRANSCRIPTION_MAP['T'] = 'A';
    TRANSCRIPTION_MAP['A'] = 'U';
  }

  String transcribe(String dnaStrand) {
    if (dnaStrand.isEmpty()) {
      return "";
    }
    
    char[] result = new char[dnaStrand.length()];
    for (int i = 0; i < dnaStrand.length(); i++) {
      result[i] = TRANSCRIPTION_MAP[dnaStrand.charAt(i)];
    }
    return new String(result);
  }

  private String transcribeRNA(String rna) {
    if (rna.length() == 1) {
      return String.valueOf(TRANSCRIPTION_MAP[rna.charAt(0)]);
    }
    return "";
  }
}