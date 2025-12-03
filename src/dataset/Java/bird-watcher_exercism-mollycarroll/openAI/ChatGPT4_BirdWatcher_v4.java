import java.util.Arrays;

class BirdWatcher {
    private final int[] birdsPerDay;

    public BirdWatcher(int[] birdsPerDay) {
        this.birdsPerDay = Arrays.copyOf(birdsPerDay, birdsPerDay.length);
    }

    public int[] getLastWeek() {
        return Arrays.copyOf(birdsPerDay, birdsPerDay.length);
    }

    public int getToday() {
        return birdsPerDay.length == 7 ? birdsPerDay[6] : 0;
    }

    public void incrementTodaysCount() {
        if (birdsPerDay.length == 7) {
            birdsPerDay[6]++;
        }
    }

    public boolean hasDayWithoutBirds() {
        return Arrays.stream(birdsPerDay).anyMatch(birdCount -> birdCount == 0);
    }

    public int getCountForFirstDays(int numberOfDays) {
        return Arrays.stream(birdsPerDay, 0, Math.min(numberOfDays, birdsPerDay.length)).sum();
    }

    public int getBusyDays() {
        return (int) Arrays.stream(birdsPerDay).filter(birdCount -> birdCount >= 5).count();
    }
}