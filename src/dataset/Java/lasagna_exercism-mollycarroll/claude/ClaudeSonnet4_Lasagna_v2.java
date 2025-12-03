public class Lasagna {
    private static final int EXPECTED_MINUTES_IN_OVEN = 40;
    private static final int PREPARATION_TIME_PER_LAYER = 2;

    public static int expectedMinutesInOven() {
        return EXPECTED_MINUTES_IN_OVEN;
    }

    public static int remainingMinutesInOven(int minutes) {
        return EXPECTED_MINUTES_IN_OVEN - minutes;
    }

    public static int preparationTimeInMinutes(int layers) {
        return layers << 1;
    }

    public static int totalTimeInMinutes(int layers, int minutes) {
        return (layers << 1) + minutes;
    }
}