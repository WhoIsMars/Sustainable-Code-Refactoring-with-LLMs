public class SpaceAge {
    private final long seconds;
    private static final double EARTH_YEAR_SECONDS = 31557600.0;

    public SpaceAge(long seconds) {
        this.seconds = seconds;
    }

    public SpaceAge(int seconds) {
        this.seconds = seconds;
    }

    public long getSeconds() {
        return this.seconds;
    }

    public double onEarth() {
        return seconds / EARTH_YEAR_SECONDS;
    }

    public double onMercury() {
        return seconds / (EARTH_YEAR_SECONDS * 0.2408467);
    }

    public double onVenus() {
        return seconds / (EARTH_YEAR_SECONDS * 0.61519726);
    }

    public double onMars() {
        return seconds / (EARTH_YEAR_SECONDS * 1.8808158);
    }

    public double onJupiter() {
        return seconds / (EARTH_YEAR_SECONDS * 11.862615);
    }

    public double onSaturn() {
        return seconds / (EARTH_YEAR_SECONDS * 29.447498);
    }

    public double onUranus() {
        return seconds / (EARTH_YEAR_SECONDS * 84.016846);
    }

    public double onNeptune() {
        return seconds / (EARTH_YEAR_SECONDS * 164.79132);
    }
}