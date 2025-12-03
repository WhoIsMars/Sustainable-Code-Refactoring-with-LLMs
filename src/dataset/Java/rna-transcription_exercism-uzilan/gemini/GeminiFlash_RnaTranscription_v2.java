class RnaTranscription {

    private static final char[] transcriptionMap = new char[256];

    static {
        for (int i = 0; i < transcriptionMap.length; i++) {
            transcriptionMap[i] = '?'; // Default value
        }
        transcriptionMap['C'] = 'G';
        transcriptionMap['G'] = 'C';
        transcriptionMap['T'] = 'A';
        transcriptionMap['A'] = 'U';
    }

    String transcribe(String dnaStrand) {
        StringBuilder rnaStrand = new StringBuilder(dnaStrand.length());
        for (int i = 0; i < dnaStrand.length(); i++) {
            char dnaNucleotide = dnaStrand.charAt(i);
            rnaStrand.append(transcriptionMap[dnaNucleotide]);
        }
        return rnaStrand.toString();
    }
}