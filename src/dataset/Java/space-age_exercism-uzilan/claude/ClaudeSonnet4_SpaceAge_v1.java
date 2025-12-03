class SpaceAge {

    private final double seconds;
    private static final double EARTH_ORBITAL_PERIOD = 31557600.0; // in seconds
    
    // Pre-calculated reciprocals to avoid division operations
    private static final double MERCURY_FACTOR = 1.0 / (0.2408467 * EARTH_ORBITAL_PERIOD);
    private static final double VENUS_FACTOR = 1.0 / (0.61519726 * EARTH_ORBITAL_PERIOD);
    private static final double EARTH_FACTOR = 1.0 / EARTH_ORBITAL_PERIOD;
    private static final double MARS_FACTOR = 1.0 / (1.8808158 * EARTH_ORBITAL_PERIOD);
    private static final double JUPITER_FACTOR = 1.0 / (11.862615 * EARTH_ORBITAL_PERIOD);
    private static final double SATURN_FACTOR = 1.0 / (29.447498 * EARTH_ORBITAL_PERIOD);
    private static final double URANUS_FACTOR = 1.0 / (84.016846 * EARTH_ORBITAL_PERIOD);
    private static final double NEPTUNE_FACTOR = 1.0 / (164.79132 * EARTH_ORBITAL_PERIOD);

    SpaceAge(double seconds) {
        this.seconds = seconds;
    }

    double onEarth() {
        return seconds * EARTH_FACTOR;
    }

    double onMercury() {
        return seconds * MERCURY_FACTOR;
    }

    double onVenus() {
        return seconds * VENUS_FACTOR;
    }

    double onMars() {
        return seconds * MARS_FACTOR;
    }

    double onJupiter() {
        return seconds * JUPITER_FACTOR;
    }

    double onSaturn() {
        return seconds * SATURN_FACTOR;
    }

    double onUranus() {
        return seconds * URANUS_FACTOR;
    }

    double onNeptune() {
        return seconds * NEPTUNE_FACTOR;
    }
}