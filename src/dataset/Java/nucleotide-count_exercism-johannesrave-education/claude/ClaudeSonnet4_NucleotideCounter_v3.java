import java.util.HashMap;

class NucleotideCounter{
    private final String nucleotides;
    private final HashMap<Character, Integer> counts = new HashMap<Character, Integer>(4, 1.0f); 
    private boolean counted = false;
    
    public NucleotideCounter(String nucleotides) {
        if (nucleotides == null || nucleotides.matches(".*[^ACGT].*")){
            throw new IllegalArgumentException();
        }
        this.nucleotides = nucleotides;
        counts.put('A', 0);
        counts.put('C', 0);
        counts.put('G', 0);
        counts.put('T', 0);
    }

    public HashMap nucleotideCounts(){
        if (!counted) {
            for (int i = 0; i < nucleotides.length(); i++) {
                char c = nucleotides.charAt(i);
                counts.put(c, counts.get(c) + 1);
            }
            counted = true;
        }
        return counts;
    }
}