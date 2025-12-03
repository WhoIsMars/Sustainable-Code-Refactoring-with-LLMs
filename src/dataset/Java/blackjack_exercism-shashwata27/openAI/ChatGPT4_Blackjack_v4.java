import java.util.Map;

public class Blackjack {

    private static final Map<String, Integer> CARD_VALUES = Map.of(
            "ace", 11,
            "ten", 10,
            "jack", 10,
            "queen", 10,
            "king", 10,
            "two", 2,
            "three", 3,
            "four", 4,
            "five", 5,
            "six", 6,
            "seven", 7,
            "eight", 8,
            "nine", 9
    );

    public int parseCard(String card) {
        return CARD_VALUES.getOrDefault(card, 0);
    }

    public boolean isBlackjack(String card1, String card2) {
        return parseCard(card1) + parseCard(card2) == 21;
    }

    public String largeHand(boolean isBlackjack, int dealerScore) {
        return isBlackjack ? (dealerScore < 10 ? "W" : "S") : "P";
    }

    public String smallHand(int handScore, int dealerScore) {
        if (handScore >= 17) {
            return "S";
        } else if (handScore <= 11) {
            return "H";
        } else {
            return dealerScore < 7 ? "S" : "H";
        }
    }

    public String firstTurn(String card1, String card2, String dealerCard) {
        int handScore = parseCard(card1) + parseCard(card2);
        int dealerScore = parseCard(dealerCard);

        return handScore > 20 ? largeHand(isBlackjack(card1, card2), dealerScore) : smallHand(handScore, dealerScore);
    }
}