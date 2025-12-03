class SpaceAge {

    private final double seconds;
    private static final double EARTH_ORBITAL_PERIOD = 31557600.0;
    private static final double MERCURY_ORBITAL_PERIOD = 0.2408467 * EARTH_ORBITAL_PERIOD;
    private static final double VENUS_ORBITAL_PERIOD = 0.61519726 * EARTH_ORBITAL_PERIOD;
    private static final double MARS_ORBITAL_PERIOD = 1.8808158 * EARTH_ORBITAL_PERIOD;
    private static final double JUPITER_ORBITAL_PERIOD = 11.862615 * EARTH_ORBITAL_PERIOD;
    private static final double SATURN_ORBITAL_PERIOD = 29.447498 * EARTH_ORBITAL_PERIOD;
    private static final double URANUS_ORBITAL_PERIOD = 84.016846 * EARTH_ORBITAL_PERIOD;
    private static final double NEPTUNE_ORBITAL_PERIOD = 164.79132 * EARTH_ORBITAL_PERIOD;


    SpaceAge(double seconds) {
        this.seconds = seconds;
    }

    double onEarth() {
        return seconds / EARTH_ORBITAL_PERIOD;
    }

    double onMercury() {
        return seconds / MERCURY_ORBITAL_PERIOD;
    }

    double onVenus() {
        return seconds / VENUS_ORBITAL_PERIOD;
    }

    double onMars() {
        return seconds / MARS_ORBITAL_PERIOD;
    }

    double onJupiter() {
        return seconds / JUPITER_ORBITAL_PERIOD;
    }

    double onSaturn() {
        return seconds / SATURN_ORBITAL_PERIOD;
    }

    double onUranus() {
        return seconds / URANUS_ORBITAL_PERIOD;
    }

    double onNeptune() {
        return seconds / NEPTUNE_ORBITAL_PERIOD;
    }
}