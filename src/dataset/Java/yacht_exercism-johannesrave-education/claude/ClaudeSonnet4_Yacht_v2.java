import java.util.Arrays;

class Yacht {

    private final int[] dice;
    private final YachtCategory category;

    Yacht(int[] dice, YachtCategory yachtCategory) {
        this.dice = dice;
        this.category = yachtCategory;
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

    private int sumOfNum(int i) {
        int sum = 0;
        for (int die : dice) {
            if (die == i) sum += i;
        }
        return sum;
    }
    
    private int fullHouse() {
        int[] counts = getCounts();
        Arrays.sort(counts);
        return (counts[5] == 3 && counts[4] == 2) ? summed() : 0;
    }
    
    private int fourOfAKind() {
        int[] counts = getCounts();
        for (int i = 0; i < 6; i++) {
            if (counts[i] >= 4) {
                return 4 * (i + 1);
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
        int[] sortedDice = dice.clone();
        Arrays.sort(sortedDice);
        
        if (category == YachtCategory.LITTLE_STRAIGHT) {
            return (sortedDice[0] == 1 && sortedDice[1] == 2 && sortedDice[2] == 3 && 
                    sortedDice[3] == 4 && sortedDice[4] == 5) ? 30 : 0;
        } else {
            return (sortedDice[0] == 2 && sortedDice[1] == 3 && sortedDice[2] == 4 && 
                    sortedDice[3] == 5 && sortedDice[4] == 6) ? 30 : 0;
        }
    }
    
    private int yacht() {
        int first = dice[0];
        for (int die : dice) {
            if (die != first) return 0;
        }
        return 50;
    }
    
    private int[] getCounts() {
        int[] counts = new int[6];
        for (int die : dice) {
            counts[die - 1]++;
        }
        return counts;
    }
}