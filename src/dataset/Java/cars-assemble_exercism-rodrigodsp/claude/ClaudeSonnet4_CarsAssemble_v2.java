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
        double baseProduction = speed * 221.0;
        
        if (speed >= 10) {
            return (int)(baseProduction * 0.77 / 60);
        } else if (speed == 9) {
            return (int)(baseProduction * 0.8 / 60);
        } else if (speed >= 5) {
            return (int)(baseProduction * 0.9 / 60);
        }
        
        return (int)(baseProduction / 60);
    }
}