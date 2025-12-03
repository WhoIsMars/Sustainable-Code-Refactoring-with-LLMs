import java.util.EnumMap;
import java.util.Map;

public enum Allergen {
    EGGS(1),
    PEANUTS(2),
    SHELLFISH(4),
    STRAWBERRIES(8),
    TOMATOES(16),
    CHOCOLATE(32),
    POLLEN(64),
    CATS(128);

    private static final Map<Allergen, Integer> SCORE_MAP = new EnumMap<>(Allergen.class);

    static {
        for (Allergen allergen : values()) {
            SCORE_MAP.put(allergen, allergen.score);
        }
    }

    private final int score;

    Allergen(int score) {
        this.score = score;
    }

    public int getScore() {
        return SCORE_MAP.get(this);
    }
}