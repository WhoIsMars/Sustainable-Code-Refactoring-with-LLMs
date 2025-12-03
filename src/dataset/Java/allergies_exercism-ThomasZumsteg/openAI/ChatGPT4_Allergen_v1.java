public enum Allergen {
    EGGS(1),
    PEANUTS(2),
    SHELLFISH(4),
    STRAWBERRIES(8),
    TOMATOES(16),
    CHOCOLATE(32),
    POLLEN(64),
    CATS(128);

    private final int score;

    private static final Allergen[] VALUES = values();

    Allergen(int score) {
        this.score = score;
    }

    public int getScore() {
        return score;
    }

    public static Allergen[] getAllergens() {
        return VALUES;
    }
}