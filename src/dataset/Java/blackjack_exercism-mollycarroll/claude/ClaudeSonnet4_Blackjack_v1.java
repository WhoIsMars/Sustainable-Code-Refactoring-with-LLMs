public class Blackjack {
    
    private static final java.util.Map<String, Integer> CARD_VALUES = java.util.Map.ofEntries(
        java.util.Map.entry("ace", 11),
        java.util.Map.entry("two", 2),
        java.util.Map.entry("three", 3),
        java.util.Map.entry("four", 4),
        java.util.Map.entry("five", 5),
        java.util.Map.entry("six", 6),
        java.util.Map.entry("seven", 7),
        java.util.Map.entry("eight", 8),
        java.util.Map.entry("nine", 9),
        java.util.Map.entry("ten", 10),
        java.util.Map.entry("jack", 10),
        java.util.Map.entry("queen", 10),
        java.util.Map.entry("king", 10)
    );

    public int parseCard(String card) {
        return CARD_VALUES.getOrDefault(card, 0);
    }

    public boolean isBlackjack(String card1, String card2) {
        return parseCard(card1) + parseCard(card2) == 21;
    }

    public String largeHand(boolean isBlackjack, int dealerScore) {
        return isBlackjack && dealerScore < 10 ? "W" : isBlackjack ? "S" : "P";
    }

    public String smallHand(int handScore, int dealerScore) {
        return handScore >= 17 ? "S" : (handScore <= 11 || dealerScore >= 7) ? "H" : "S";
    }

    public String firstTurn(String card1, String card2, String dealerCard) {
        int handScore = parseCard(card1) + parseCard(card2);
        int dealerScore = parseCard(dealerCard);

        return handScore > 20 ? largeHand(isBlackjack(card1, card2), dealerScore) : smallHand(handScore, dealerScore);
    }
}