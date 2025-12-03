enum Allergen {
    EGGS(1),
    PEANUTS(2),
    SHELLFISH(4),
    STRAWBERRIES(8),
    TOMATOES(16),
    CHOCOLATE(32),
    POLLEN(64),
    CATS(128);

    private final int score;
    private static final Allergen[] allergenValues = Allergen.values();

    Allergen(int score) {
        this.score = score;
    }

    int getScore() {
        return score;
    }

    static Allergen fromScore(int score) {
        for (Allergen allergen : allergenValues) {
            if (allergen.score == score) {
                return allergen;
            }
        }
        return null; // Or throw an exception if appropriate
    }
}