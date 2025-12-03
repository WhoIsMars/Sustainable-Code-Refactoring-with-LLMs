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

    Allergen(int score) {
        this.score = score;
    }

    public int getScore() {
        return score;
    }

    private static final Map<Integer, Allergen> SCORE_TO_ALLERGEN_MAP = 
        Arrays.stream(values()).collect(Collectors.toMap(Allergen::getScore, allergen -> allergen));

    public static Allergen fromScore(int score) {
        return SCORE_TO_ALLERGEN_MAP.get(score);
    }
}