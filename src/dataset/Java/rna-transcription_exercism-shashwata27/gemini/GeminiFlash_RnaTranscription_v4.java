import java.util.Map;

class RnaTranscription {

    String transcribe(String dnaStrand) {
        Map<Character, Character> rna = Map.of(
                'G', 'C',
                'C', 'G',
                'T', 'A',
                'A', 'U'
        );

        StringBuilder ret = new StringBuilder(dnaStrand.length());
        for (int i = 0; i < dnaStrand.length(); i++) {
            ret.append(rna.get(dnaStrand.charAt(i)));
        }
        return ret.toString();
    }
}