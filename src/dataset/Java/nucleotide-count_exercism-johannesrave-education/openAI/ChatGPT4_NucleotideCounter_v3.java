import java.util.EnumMap;
import java.util.Map;

class NucleotideCounter {
    private final Map<Character, Integer> counts;

    public NucleotideCounter(String nucleotides) {
        if (!nucleotides.matches("[ACGT]*")) {
            throw new IllegalArgumentException();
        }
        counts = new EnumMap<>(Map.of(
            'A', 0,
            'C', 0,
            'G', 0,
            'T', 0
        ));
        for (char c : nucleotides.toCharArray()) {
            counts.put(c, counts.get(c) + 1);
        }
    }

    public Map<Character, Integer> nucleotideCounts() {
        return counts;
    }
}