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
        for (char strand : dnaStrand.toCharArray()) {
            ret.append(rna.get(strand));
        }
        return ret.toString();
    }

}