class RnaTranscription {

    String transcribe(String dnaStrand) {
        int length = dnaStrand.length();
        StringBuilder answer = new StringBuilder(length);
        
        for (int i = 0; i < length; i++) {
            char temp = dnaStrand.charAt(i);
            switch (temp) {
                case 'G':
                    answer.append('C');
                    break;
                case 'C':
                    answer.append('G');
                    break;
                case 'T':
                    answer.append('A');
                    break;
                case 'A':
                    answer.append('U');
                    break;
                default:
                    return "";
            }
        }
        return answer.toString();
    }
}