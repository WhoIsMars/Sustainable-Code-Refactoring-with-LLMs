import java.util.HashMap;

class NucleotideCounter{
    private final String nucleotides;
    private final HashMap<Character, Integer> counts = new HashMap<Character, Integer>(4, 1.0f); 
    
    public NucleotideCounter(String nucleotides) {
        final int length = nucleotides.length();
        for (int i = 0; i < length; i++) {
            final char c = nucleotides.charAt(i);
            if (c != 'A' && c != 'C' && c != 'G' && c != 'T') {
                throw new IllegalArgumentException();
            }
        }
        this.nucleotides = nucleotides;
        counts.put('A', 0);
        counts.put('C', 0);
        counts.put('G', 0);
        counts.put('T', 0);
    }

    public HashMap nucleotideCounts(){
        final int length = nucleotides.length();
        for (int i = 0; i < length; i++) {
            final char c = nucleotides.charAt(i);
            counts.put(c, counts.get(c) + 1);
        }
        return counts;
    }
}