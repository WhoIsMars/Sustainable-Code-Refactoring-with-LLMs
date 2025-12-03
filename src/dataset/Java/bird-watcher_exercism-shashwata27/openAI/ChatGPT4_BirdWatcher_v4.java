class BirdWatcher {
    private final int[] birdsPerDay;

    public BirdWatcher(int[] birdsPerDay) {
        this.birdsPerDay = birdsPerDay.clone();
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
        for (int cnt : birdsPerDay) {
            if (cnt == 0) {
                return true;
            }
        }
        return false;
    }

    public int getCountForFirstDays(int numberOfDays) {
        int limit = Math.min(numberOfDays, Math.min(birdsPerDay.length, 7));
        int cnt = 0;
        for (int i = 0; i < limit; i++) {
            cnt += birdsPerDay[i];
        }
        return cnt;
    }

    public int getBusyDays() {
        int busyDays = 0;
        for (int bird : birdsPerDay) {
            if (bird >= 5) {
                busyDays++;
            }
        }
        return busyDays;
    }
}