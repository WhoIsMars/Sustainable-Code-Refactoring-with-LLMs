public class CarsAssemble {

    private static final int PRODUCTION_PER_HOUR = 221;

    public double productionRatePerHour(int speed) {
        double rate;
        switch (speed) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                rate = 1.0;
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                rate = 0.9;
                break;
            case 9:
                rate = 0.8;
                break;
            default:
                rate = 0.77;
                break;
        }
        return speed * PRODUCTION_PER_HOUR * rate;
    }

    public int workingItemsPerMinute(int speed) {
        return (int) (productionRatePerHour(speed) / 60.0);
    }
}