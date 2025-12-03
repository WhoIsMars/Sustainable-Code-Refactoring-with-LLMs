public class CarsAssemble {

    public double productionRatePerHour(int speed) {
        double baseProduction = speed * 221.0;
        
        if (speed >= 10) {
            return baseProduction * 0.77;
        } else if (speed == 9) {
            return baseProduction * 0.8;
        } else if (speed >= 5) {
            return baseProduction * 0.9;
        }
        
        return baseProduction;
    }

    public int workingItemsPerMinute(int speed) {
        return (int)(productionRatePerHour(speed) / 60);
    }
}