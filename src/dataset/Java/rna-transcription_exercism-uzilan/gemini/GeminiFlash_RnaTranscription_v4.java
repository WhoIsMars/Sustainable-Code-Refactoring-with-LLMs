class RnaTranscription {

    String transcribe(String dnaStrand) {
        int length = dnaStrand.length();
        StringBuilder rna = new StringBuilder(length);
        for (int i = 0; i < length; i++) {
            char dnaNucleotide = dnaStrand.charAt(i);
            char rnaNucleotide;
            switch (dnaNucleotide) {
                case 'C':
                    rnaNucleotide = 'G';
                    break;
                case 'G':
                    rnaNucleotide = 'C';
                    break;
                case 'T':
                    rnaNucleotide = 'A';
                    break;
                case 'A':
                    rnaNucleotide = 'U';
                    break;
                default:
                    rnaNucleotide = '?';
                    break;
            }
            rna.append(rnaNucleotide);
        }
        return rna.toString();
    }
}