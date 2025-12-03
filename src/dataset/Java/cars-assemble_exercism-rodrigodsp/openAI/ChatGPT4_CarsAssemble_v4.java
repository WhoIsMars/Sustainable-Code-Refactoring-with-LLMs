public class CarsAssemble {

    public double productionRatePerHour(int speed) {
        if (speed == 0) return 0;

        double successRate = speed < 5 ? 1.0 :
                             speed < 9 ? 0.9 :
                             speed == 9 ? 0.8 : 0.77;

        return speed * 221 * successRate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) (productionRatePerHour(speed) / 60);
    }
}