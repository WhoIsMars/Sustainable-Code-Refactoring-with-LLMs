class RnaTranscription {

    String transcribe(String dnaStrand) {
        StringBuilder rna = new StringBuilder(dnaStrand.length());
        for (int i = 0; i < dnaStrand.length(); i++) {
            char c = dnaStrand.charAt(i);
            switch (c) {
                case 'C':
                    rna.append('G');
                    break;
                case 'G':
                    rna.append('C');
                    break;
                case 'T':
                    rna.append('A');
                    break;
                case 'A':
                    rna.append('U');
                    break;
                default:
                    rna.append('?');
            }
        }
        return rna.toString();
    }
}