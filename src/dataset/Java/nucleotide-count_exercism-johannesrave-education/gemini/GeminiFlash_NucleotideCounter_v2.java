import java.util.HashMap;

class NucleotideCounter{
    private final String nucleotides;
    private final HashMap<Character, Integer> counts = new HashMap<>();

    public NucleotideCounter(String nucleotides) {
        if (!nucleotides.matches("[ACGT]*")){
            throw new IllegalArgumentException();
        }
        this.nucleotides = nucleotides;
        counts.put('A', 0);
        counts.put('C', 0);
        counts.put('G', 0);
        counts.put('T', 0);
    }

    public HashMap<Character, Integer> nucleotideCounts(){
        for (int i = 0; i < nucleotides.length(); i++) {
            char c = nucleotides.charAt(i);
            counts.put(c, counts.get(c) + 1);
        }
        return new HashMap<>(counts);
    }
}