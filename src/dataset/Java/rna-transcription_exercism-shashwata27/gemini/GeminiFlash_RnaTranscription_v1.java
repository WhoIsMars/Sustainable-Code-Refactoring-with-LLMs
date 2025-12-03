import java.util.Map;

class RnaTranscription {

    private static final Map<Character, Character> RNA_MAP = Map.of(
            'G', 'C',
            'C', 'G',
            'T', 'A',
            'A', 'U'
    );

    String transcribe(String dnaStrand) {
        StringBuilder rnaStrand = new StringBuilder(dnaStrand.length());
        for (int i = 0; i < dnaStrand.length(); i++) {
            char dnaNucleotide = dnaStrand.charAt(i);
            rnaStrand.append(RNA_MAP.get(dnaNucleotide));
        }
        return rnaStrand.toString();
    }
}