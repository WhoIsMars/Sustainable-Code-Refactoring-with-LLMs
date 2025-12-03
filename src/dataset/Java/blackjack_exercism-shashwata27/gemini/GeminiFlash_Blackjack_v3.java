import java.util.Map;

public class Blackjack {

    private static final Map<String, Integer> CARD_VALUES = Map.ofEntries(
            Map.entry("ace", 11),
            Map.entry("ten", 10),
            Map.entry("jack", 10),
            Map.entry("queen", 10),
            Map.entry("king", 10),
            Map.entry("two", 2),
            Map.entry("three", 3),
            Map.entry("four", 4),
            Map.entry("five", 5),
            Map.entry("six", 6),
            Map.entry("seven", 7),
            Map.entry("eight", 8),
            Map.entry("nine", 9)
    );

    public int parseCard(String card) {
        Integer value = CARD_VALUES.get(card);
        return (value != null) ? value : 0;
    }

    public boolean isBlackjack(String card1, String card2) {
        int val1 = parseCard(card1);
        int val2 = parseCard(card2);
        return (val1 + val2 == 21);
    }

    public String largeHand(boolean isBlackjack, int dealerScore) {
        if (isBlackjack) {
            return (dealerScore < 10) ? "W" : "S";
        }
        return "P";
    }

    public String smallHand(int handScore, int dealerScore) {
        if (handScore >= 17) {
            return "S";
        } else if (handScore <= 11) {
            return "H";
        } else {
            return (dealerScore < 7) ? "S" : "H";
        }
    }

    public String firstTurn(String card1, String card2, String dealerCard) {
        int handScore = parseCard(card1) + parseCard(card2);
        int dealerScore = parseCard(dealerCard);

        if (handScore > 20) {
            return largeHand(isBlackjack(card1, card2), dealerScore);
        } else {
            return smallHand(handScore, dealerScore);
        }
    }
}