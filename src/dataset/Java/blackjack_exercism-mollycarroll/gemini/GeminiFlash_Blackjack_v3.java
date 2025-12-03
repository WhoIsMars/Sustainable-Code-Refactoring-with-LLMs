public class Blackjack {

    private static final int ACE_VALUE = 11;
    private static final int FACE_CARD_VALUE = 10;

    public int parseCard(String card) {
        return switch (card) {
            case "ace" -> ACE_VALUE;
            case "two" -> 2;
            case "three" -> 3;
            case "four" -> 4;
            case "five" -> 5;
            case "six" -> 6;
            case "seven" -> 7;
            case "eight" -> 8;
            case "nine" -> 9;
            case "ten", "jack", "queen", "king" -> FACE_CARD_VALUE;
            default -> 0;
        };
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
        }
        return (handScore <= 11 || dealerScore >= 7) ? "H" : "S";
    }

    public String firstTurn(String card1, String card2, String dealerCard) {
        int handScore = parseCard(card1) + parseCard(card2);
        int dealerScore = parseCard(dealerCard);

        return (20 < handScore) ? largeHand(isBlackjack(card1, card2), dealerScore) : smallHand(handScore, dealerScore);
    }
}