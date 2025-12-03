class RnaTranscription {

    String transcribe(String dnaStrand) {
        char[] result = new char[dnaStrand.length()];
        for (int i = 0; i < dnaStrand.length(); i++) {
            switch (dnaStrand.charAt(i)) {
                case 'C':
                    result[i] = 'G';
                    break;
                case 'G':
                    result[i] = 'C';
                    break;
                case 'T':
                    result[i] = 'A';
                    break;
                case 'A':
                    result[i] = 'U';
                    break;
                default:
                    result[i] = '?';
                    break;
            }
        }
        return new String(result);
    }
}