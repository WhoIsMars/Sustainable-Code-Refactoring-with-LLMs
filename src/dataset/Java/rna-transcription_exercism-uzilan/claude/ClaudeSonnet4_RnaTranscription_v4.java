class RnaTranscription {

    String transcribe(String dnaStrand) {
        if (dnaStrand.isEmpty()) {
            return "";
        }
        
        StringBuilder result = new StringBuilder(dnaStrand.length());
        
        for (int i = 0; i < dnaStrand.length(); i++) {
            char c = dnaStrand.charAt(i);
            switch (c) {
                case 'C':
                    result.append('G');
                    break;
                case 'G':
                    result.append('C');
                    break;
                case 'T':
                    result.append('A');
                    break;
                case 'A':
                    result.append('U');
                    break;
                default:
                    result.append('?');
                    break;
            }
        }
        
        return result.toString();
    }
}