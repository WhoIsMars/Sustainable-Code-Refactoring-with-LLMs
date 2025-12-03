public class Blackjack {

    private static final int ACE_VALUE = 11;
    private static final int FACE_CARD_VALUE = 10;

    public int parseCard(String card) {
        switch (card) {
            case "ace":
                return ACE_VALUE;
            case "two":
                return 2;
            case "three":
                return 3;
            case "four":
                return 4;
            case "five":
                return 5;
            case "six":
                return 6;
            case "seven":
                return 7;
            case "eight":
                return 8;
            case "nine":
                return 9;
            case "ten":
            case "jack":
            case "queen":
            case "king":
                return FACE_CARD_VALUE;
            default:
                return 0;
        }
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
        if (handScore <= 11 || dealerScore >= 7) {
            return "H";
        }
        return "S";
    }

    public String firstTurn(String card1, String card2, String dealerCard) {
        int handScore = parseCard(card1) + parseCard(card2);
        int dealerScore = parseCard(dealerCard);

        return (handScore > 20) ? largeHand(isBlackjack(card1, card2), dealerScore) : smallHand(handScore, dealerScore);
    }
}