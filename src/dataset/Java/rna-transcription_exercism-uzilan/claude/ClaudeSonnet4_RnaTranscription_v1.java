class RnaTranscription {
    private static final char[] DNA_TO_RNA = new char[256];
    
    static {
        DNA_TO_RNA['C'] = 'G';
        DNA_TO_RNA['G'] = 'C';
        DNA_TO_RNA['T'] = 'A';
        DNA_TO_RNA['A'] = 'U';
    }

    String transcribe(String dnaStrand) {
        char[] result = new char[dnaStrand.length()];
        for (int i = 0; i < dnaStrand.length(); i++) {
            char c = dnaStrand.charAt(i);
            char transcribed = DNA_TO_RNA[c];
            result[i] = transcribed != 0 ? transcribed : '?';
        }
        return new String(result);
    }
}