import java.util.Arrays;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;
    private int[] counts;
    private int sum;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
        precompute();
    }

    private void precompute() {
        counts = new int[7];
        sum = 0;
        for (int die : dice) {
            counts[die]++;
            sum += die;
        }
    }

    int score() {
        switch (category){
            case ONES: return counts[1];
            case TWOS: return counts[2] << 1;
            case THREES: return counts[3] * 3;
            case FOURS: return counts[4] << 2;
            case FIVES: return counts[5] * 5;
            case SIXES: return counts[6] * 6;
            case FULL_HOUSE: return fullHouse();
            case FOUR_OF_A_KIND: return fourOfAKind();
            case LITTLE_STRAIGHT:
            case BIG_STRAIGHT: return straight();
            case CHOICE: return sum;
            case YACHT: return yacht();
            default: return 0; 
        }
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
        return (hasThree && hasTwo) ? sum : 0;
    }
    
    private int fourOfAKind() {
        for (int i = 1; i <= 6; i++) {
            if (counts[i] >= 4){
                return i << 2;
            }
        }
        return 0;
    }

    private int summed() {
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
        for (int i = 1; i <= 6; i++) {
            if (counts[i] == 5) return 50;
        }
        return 0;
    }
    
    private int occurs(int die){
        return counts[die];
    }
}