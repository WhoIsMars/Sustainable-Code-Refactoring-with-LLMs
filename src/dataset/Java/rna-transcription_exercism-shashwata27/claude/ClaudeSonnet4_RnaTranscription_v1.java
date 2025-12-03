import java.util.Map;

class RnaTranscription {
    
    private static final Map<Character, Character> RNA_MAP = Map.of(
            'G', 'C',
            'C', 'G',
            'T', 'A',
            'A', 'U'
    );

    String transcribe(String dnaStrand) {
        StringBuilder ret = new StringBuilder(dnaStrand.length());
        for (int i = 0; i < dnaStrand.length(); i++) {
            ret.append(RNA_MAP.get(dnaStrand.charAt(i)));
        }
        return ret.toString();
    }
}