import java.util.HashMap;

class NucleotideCounter{
    private final String nucleotides;
    private final HashMap<Character, Integer> counts = new HashMap<Character, Integer>(); 
    
    public NucleotideCounter(String nucleotides) {
        this.nucleotides = nucleotides;
        counts.put('A', 0);
        counts.put('C', 0);
        counts.put('G', 0);
        counts.put('T', 0);
        
        // Validate and count in one pass
        for (int i = 0; i < nucleotides.length(); i++) {
            char c = nucleotides.charAt(i);
            if (c == 'A' || c == 'C' || c == 'G' || c == 'T') {
                counts.put(c, counts.get(c) + 1);
            } else {
                throw new IllegalArgumentException();
            }
        }
    }

    public HashMap nucleotideCounts(){
        return counts;
    }
}