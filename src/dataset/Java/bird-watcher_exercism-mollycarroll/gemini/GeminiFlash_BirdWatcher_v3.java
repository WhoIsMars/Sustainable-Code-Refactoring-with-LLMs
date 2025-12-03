class BirdWatcher {
    private final int[] birdsPerDay;

    public BirdWatcher(int[] birdsPerDay) {
        this.birdsPerDay = birdsPerDay.clone();
    }

    public int[] getLastWeek() {
        return birdsPerDay.clone();
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
        for (int birdCount : birdsPerDay) {
            if (birdCount == 0) {
                return true;
            }
        }
        return false;
    }

    public int getCountForFirstDays(int numberOfDays) {
        int total = 0;
        int limit = Math.min(birdsPerDay.length, numberOfDays);
        for (int i = 0; i < limit; i++) {
            total += birdsPerDay[i];
        }
        return total;
    }

    public int getBusyDays() {
        int busyDays = 0;
        for (int birdCount : birdsPerDay) {
            if (birdCount >= 5) {
                busyDays++;
            }
        }
        return busyDays;
    }
}