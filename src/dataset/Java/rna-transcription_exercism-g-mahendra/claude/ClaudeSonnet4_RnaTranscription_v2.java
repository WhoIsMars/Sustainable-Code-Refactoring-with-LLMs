class RnaTranscription {

    String transcribe(String dnaStrand) {
        int length = dnaStrand.length();
        char[] result = new char[length];
        
        for (int i = 0; i < length; i++) {
            char nucleotide = dnaStrand.charAt(i);
            switch (nucleotide) {
                case 'G':
                    result[i] = 'C';
                    break;
                case 'C':
                    result[i] = 'G';
                    break;
                case 'T':
                    result[i] = 'A';
                    break;
                case 'A':
                    result[i] = 'U';
                    break;
                default:
                    return "";
            }
        }
        return new String(result);
    }

}