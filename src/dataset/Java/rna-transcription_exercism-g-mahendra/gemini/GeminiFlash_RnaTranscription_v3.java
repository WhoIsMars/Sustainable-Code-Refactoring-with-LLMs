class RnaTranscription {

    String transcribe(String dnaStrand) {
        int length = dnaStrand.length();
        StringBuilder rnaStrand = new StringBuilder(length);

        for (int i = 0; i < length; i++) {
            char temp = dnaStrand.charAt(i);
            switch (temp) {
                case 'G':
                    rnaStrand.append('C');
                    break;
                case 'C':
                    rnaStrand.append('G');
                    break;
                case 'T':
                    rnaStrand.append('A');
                    break;
                case 'A':
                    rnaStrand.append('U');
                    break;
                default:
                    return "";
            }
        }
        return rnaStrand.toString();
    }
}