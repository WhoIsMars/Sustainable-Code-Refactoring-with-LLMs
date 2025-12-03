public class CarsAssemble {

    private static final int CARS_PER_HOUR = 221;

    public double productionRatePerHour(int speed) {
        double productionRate = speed * CARS_PER_HOUR;

        switch (speed) {
            case 5:
            case 6:
            case 7:
            case 8:
                productionRate *= 0.9;
                break;
            case 9:
                productionRate *= 0.8;
                break;
            case 10:
                productionRate *= 0.77;
                break;
        }

        return productionRate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int)(productionRatePerHour(speed) / 60);
    }
}