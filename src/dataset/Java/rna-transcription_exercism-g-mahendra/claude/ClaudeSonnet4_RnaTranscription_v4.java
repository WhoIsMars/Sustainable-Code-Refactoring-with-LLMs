class RnaTranscription {

    String transcribe(String dnaStrand) {
        int length = dnaStrand.length();
        StringBuilder result = new StringBuilder(length);
        
        for (int i = 0; i < length; i++) {
            char nucleotide = dnaStrand.charAt(i);
            switch (nucleotide) {
                case 'G':
                    result.append('C');
                    break;
                case 'C':
                    result.append('G');
                    break;
                case 'T':
                    result.append('A');
                    break;
                case 'A':
                    result.append('U');
                    break;
                default:
                    return "";
            }
        }
        return result.toString();
    }

}