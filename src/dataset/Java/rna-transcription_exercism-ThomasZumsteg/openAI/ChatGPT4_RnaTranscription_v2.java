public class RnaTranscription {
    public static String ofDna(String dna) {
        StringBuilder rna = new StringBuilder(dna.length());
        for (char c : dna.toCharArray()) {
            rna.append(fromDnaToRna(c));
        }
        return rna.toString();
    }

    private static char fromDnaToRna(char dna) {
        switch (dna) {
            case 'C': return 'G';
            case 'G': return 'C';
            case 'T': return 'A';
            case 'A': return 'U';
            default: throw new IllegalArgumentException("Invalid DNA nucleotide: " + dna);
        }
    }
}