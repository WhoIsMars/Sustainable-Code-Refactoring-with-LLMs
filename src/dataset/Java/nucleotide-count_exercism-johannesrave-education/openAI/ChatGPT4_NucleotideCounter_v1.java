import java.util.EnumMap;

class NucleotideCounter {
    private final EnumMap<Nucleotide, Integer> counts = new EnumMap<>(Nucleotide.class);

    public NucleotideCounter(String nucleotides) {
        if (!nucleotides.matches("[ACGT]*")) {
            throw new IllegalArgumentException();
        }
        for (Nucleotide n : Nucleotide.values()) {
            counts.put(n, 0);
        }
        for (char c : nucleotides.toCharArray()) {
            counts.put(Nucleotide.valueOf(String.valueOf(c)), counts.get(Nucleotide.valueOf(String.valueOf(c))) + 1);
        }
    }

    public EnumMap<Nucleotide, Integer> nucleotideCounts() {
        return counts;
    }

    private enum Nucleotide {
        A, C, G, T
    }
}