import java.util.Arrays;

class BirdWatcher {
    private final int[] birdsPerDay;

    public BirdWatcher(int[] birdsPerDay) {
        this.birdsPerDay = Arrays.copyOf(birdsPerDay, birdsPerDay.length);
    }

    public int[] getLastWeek() {
        return new int[]{0, 2, 5, 3, 7, 8, 4};
    }

    public int getToday() {
        return birdsPerDay.length == 0 ? 0 : birdsPerDay[birdsPerDay.length - 1];
    }

    public void incrementTodaysCount() {
        if (birdsPerDay.length > 0) {
            birdsPerDay[birdsPerDay.length - 1]++;
        }
    }

    public boolean hasDayWithoutBirds() {
        return Arrays.stream(birdsPerDay).anyMatch(cnt -> cnt == 0);
    }

    public int getCountForFirstDays(int numberOfDays) {
        return Arrays.stream(birdsPerDay, 0, Math.min(numberOfDays, birdsPerDay.length)).sum();
    }

    public int getBusyDays() {
        return (int) Arrays.stream(birdsPerDay).filter(bird -> bird >= 5).count();
    }
}