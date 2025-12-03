import java.util.Arrays;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;
    private int[] counts;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
        this.counts = computeCounts();
    }

    int score() {
        switch (category){
            case ONES: return sumOfNum(1);
            case TWOS: return sumOfNum(2);
            case THREES: return sumOfNum(3);
            case FOURS: return sumOfNum(4);
            case FIVES: return sumOfNum(5);
            case SIXES: return sumOfNum(6);
            case FULL_HOUSE: return fullHouse();
            case FOUR_OF_A_KIND: return fourOfAKind();
            case LITTLE_STRAIGHT:
            case BIG_STRAIGHT: return straight();
            case CHOICE: return summed();
            case YACHT: return yacht();
            default: return 0; 
        }
    }

    private int[] computeCounts() {
        int[] counts = new int[7];
        for (int die : dice) {
            counts[die]++;
        }
        return counts;
    }

    private int sumOfNum(int i) {
        return counts[i] * i;
    }
    
    private int fullHouse() {
        boolean hasThree = false, hasTwo = false;
        for (int i = 1; i <= 6; i++) {
            if (counts[i] == 3) hasThree = true;
            else if (counts[i] == 2) hasTwo = true;
        }
        return (hasThree && hasTwo) ? summed() : 0;
    }
    
    private int fourOfAKind() {
        for (int i = 1; i <= 6; i++) {
            if (counts[i] >= 4){
                return 4 * i;
            }
        }
        return 0;
    }

    private int summed() {
        int sum = 0;
        for (int die : dice) {
            sum += die;
        }
        return sum;
    }

    private int straight() {
        if (category == YachtCategory.LITTLE_STRAIGHT) {
            return (counts[1] == 1 && counts[2] == 1 && counts[3] == 1 && 
                   counts[4] == 1 && counts[5] == 1) ? 30 : 0;
        } else {
            return (counts[2] == 1 && counts[3] == 1 && counts[4] == 1 && 
                   counts[5] == 1 && counts[6] == 1) ? 30 : 0;
        }
    }
    
    private int yacht() {
        return (counts[dice[0]] == 5) ? 50 : 0;
    }
    
    private int occurs(int die){
        return counts[die];
    }
}