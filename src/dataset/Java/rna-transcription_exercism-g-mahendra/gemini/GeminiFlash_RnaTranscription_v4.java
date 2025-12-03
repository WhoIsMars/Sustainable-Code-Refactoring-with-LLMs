class RnaTranscription {

    String transcribe(String dnaStrand) {
        int length = dnaStrand.length();
        StringBuilder rna = new StringBuilder(length);

        for (int i = 0; i < length; i++) {
            char dnaNucleotide = dnaStrand.charAt(i);
            switch (dnaNucleotide) {
                case 'G':
                    rna.append('C');
                    break;
                case 'C':
                    rna.append('G');
                    break;
                case 'T':
                    rna.append('A');
                    break;
                case 'A':
                    rna.append('U');
                    break;
                default:
                    return "";
            }
        }

        return rna.toString();
    }
}