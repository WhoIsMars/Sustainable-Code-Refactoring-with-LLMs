class SpaceAge {

    private final double earthYears;
    private static final double EARTH_ORBITAL_PERIOD = 31557600.0;

    private static final double MERCURY_FACTOR = 1.0 / 0.2408467;
    private static final double VENUS_FACTOR = 1.0 / 0.61519726;
    private static final double MARS_FACTOR = 1.0 / 1.8808158;
    private static final double JUPITER_FACTOR = 1.0 / 11.862615;
    private static final double SATURN_FACTOR = 1.0 / 29.447498;
    private static final double URANUS_FACTOR = 1.0 / 84.016846;
    private static final double NEPTUNE_FACTOR = 1.0 / 164.79132;

    SpaceAge(double seconds) {
        this.earthYears = seconds / EARTH_ORBITAL_PERIOD;
    }

    double onEarth() {
        return earthYears;
    }

    double onMercury() {
        return earthYears * MERCURY_FACTOR;
    }

    double onVenus() {
        return earthYears * VENUS_FACTOR;
    }

    double onMars() {
        return earthYears * MARS_FACTOR;
    }

    double onJupiter() {
        return earthYears * JUPITER_FACTOR;
    }

    double onSaturn() {
        return earthYears * SATURN_FACTOR;
    }

    double onUranus() {
        return earthYears * URANUS_FACTOR;
    }

    double onNeptune() {
        return earthYears * NEPTUNE_FACTOR;
    }
}