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
        int days = Math.min(numberOfDays, birdsPerDay.length);
        int count = 0;
        for (int i = 0; i < days; i++) {
            count += birdsPerDay[i];
        }
        return count;
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