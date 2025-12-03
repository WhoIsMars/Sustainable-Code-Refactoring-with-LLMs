import java.util.Map;

class RnaTranscription {

    private static final Map<Character, Character> TRANSCRIPTION_MAP = Map.of(
        'C', 'G',
        'G', 'C',
        'T', 'A',
        'A', 'U'
    );

    String transcribe(String dnaStrand) {
        char[] result = new char[dnaStrand.length()];
        for (int i = 0; i < dnaStrand.length(); i++) {
            result[i] = TRANSCRIPTION_MAP.getOrDefault(dnaStrand.charAt(i), '?');
        }
        return new String(result);
    }
}