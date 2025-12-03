public class SpaceAge {
    private final double seconds;
    private static final double EARTH_YEAR_IN_SECONDS = 31557600.0;
    private static final double MERCURY_ORBITAL_RATIO = 0.2408467;
    private static final double VENUS_ORBITAL_RATIO = 0.61519726;
    private static final double MARS_ORBITAL_RATIO = 1.8808158;
    private static final double JUPITER_ORBITAL_RATIO = 11.862615;
    private static final double SATURN_ORBITAL_RATIO = 29.447498;
    private static final double URANUS_ORBITAL_RATIO = 84.016846;
    private static final double NEPTUNE_ORBITAL_RATIO = 164.79132;

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
        return seconds / EARTH_YEAR_IN_SECONDS;
    }

    public double onMercury() {
        return seconds / (EARTH_YEAR_IN_SECONDS * MERCURY_ORBITAL_RATIO);
    }

    public double onVenus() {
        return seconds / (EARTH_YEAR_IN_SECONDS * VENUS_ORBITAL_RATIO);
    }

    public double onMars() {
        return seconds / (EARTH_YEAR_IN_SECONDS * MARS_ORBITAL_RATIO);
    }

    public double onJupiter() {
        return seconds / (EARTH_YEAR_IN_SECONDS * JUPITER_ORBITAL_RATIO);
    }

    public double onSaturn() {
        return seconds / (EARTH_YEAR_IN_SECONDS * SATURN_ORBITAL_RATIO);
    }

    public double onUranus() {
        return seconds / (EARTH_YEAR_IN_SECONDS * URANUS_ORBITAL_RATIO);
    }

    public double onNeptune() {
        return seconds / (EARTH_YEAR_IN_SECONDS * NEPTUNE_ORBITAL_RATIO);
    }
}