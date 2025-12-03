class RnaTranscription {

    String transcribe(String dnaStrand) {
        StringBuilder answer = new StringBuilder();
        for (int i = 0, length = dnaStrand.length(); i < length; i++) {
            switch (dnaStrand.charAt(i)) {
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