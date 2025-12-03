public class SpaceAge {
    private final double seconds;
    private static final double EARTH_YEAR_SECONDS = 31557600.0;
    private static final double MERCURY_ORBIT = 0.2408467;
    private static final double VENUS_ORBIT = 0.61519726;
    private static final double MARS_ORBIT = 1.8808158;
    private static final double JUPITER_ORBIT = 11.862615;
    private static final double SATURN_ORBIT = 29.447498;
    private static final double URANUS_ORBIT = 84.016846;
    private static final double NEPTUNE_ORBIT = 164.79132;

    public SpaceAge(Long seconds) {
        this.seconds = seconds;
    }

    public SpaceAge(Integer seconds) {
        this.seconds = seconds.doubleValue();
    }

    public Long getSeconds() {
        return (long) this.seconds;
    }

    public double onEarth() {
        return this.seconds / EARTH_YEAR_SECONDS;
    }

    public double onMercury() {
        return this.seconds / (EARTH_YEAR_SECONDS * MERCURY_ORBIT);
    }

    public double onVenus() {
        return this.seconds / (EARTH_YEAR_SECONDS * VENUS_ORBIT);
    }

    public double onMars() {
        return this.seconds / (EARTH_YEAR_SECONDS * MARS_ORBIT);
    }

    public double onJupiter() {
        return this.seconds / (EARTH_YEAR_SECONDS * JUPITER_ORBIT);
    }

    public double onSaturn() {
        return this.seconds / (EARTH_YEAR_SECONDS * SATURN_ORBIT);
    }

    public double onUranus() {
        return this.seconds / (EARTH_YEAR_SECONDS * URANUS_ORBIT);
    }

    public double onNeptune() {
        return this.seconds / (EARTH_YEAR_SECONDS * NEPTUNE_ORBIT);
    }
}