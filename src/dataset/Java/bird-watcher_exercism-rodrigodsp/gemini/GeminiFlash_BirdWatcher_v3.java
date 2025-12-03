class BirdWatcher {
    private final int[] birdsPerDay;
    private final int length;

    public BirdWatcher(int[] birdsPerDay) {
        this.birdsPerDay = birdsPerDay.clone();
        this.length = this.birdsPerDay.length;
    }

    public int[] getLastWeek() {
        return birdsPerDay.clone();
    }

    public int getToday() {
        return birdsPerDay[length - 1];
    }

    public void incrementTodaysCount() {
        birdsPerDay[length - 1]++;
    }

    public boolean hasDayWithoutBirds() {
        for (int i = 0; i < length; i++) {
            if (birdsPerDay[i] == 0) {
                return true;
            }
        }
        return false;
    }

    public int getCountForFirstDays(int numberOfDays) {
        int count = 0;
        int days = Math.min(numberOfDays, length);
        for (int i = 0; i < days; i++) {
            count += birdsPerDay[i];
        }
        return count;
    }

    public int getBusyDays() {
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (birdsPerDay[i] >= 5) {
                count++;
            }
        }
        return count;
    }
}