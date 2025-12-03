class SpaceAge {

    private final double seconds;
    private static final double EARTH_ORBITAL_PERIOD = 31557600; // in seconds

    private enum OrbitalPeriod { // in earth years
        MERCURY(0.2408467),
        VENUS(0.61519726),
        MARS(1.8808158),
        JUPITER(11.862615),
        SATURN(29.447498),
        URANUS(84.016846),
        NEPTUNE(164.79132);

        final double factor;

        OrbitalPeriod(double factor) {
            this.factor = factor * EARTH_ORBITAL_PERIOD;
        }
    }

    SpaceAge(double seconds) {
        this.seconds = seconds;
    }

    private double calculateAge(double orbitalPeriodInSeconds) {
        return seconds / orbitalPeriodInSeconds;
    }

    double onEarth() {
        return calculateAge(EARTH_ORBITAL_PERIOD);
    }

    double onMercury() {
        return calculateAge(OrbitalPeriod.MERCURY.factor);
    }

    double onVenus() {
        return calculateAge(OrbitalPeriod.VENUS.factor);
    }

    double onMars() {
        return calculateAge(OrbitalPeriod.MARS.factor);
    }

    double onJupiter() {
        return calculateAge(OrbitalPeriod.JUPITER.factor);
    }

    double onSaturn() {
        return calculateAge(OrbitalPeriod.SATURN.factor);
    }

    double onUranus() {
        return calculateAge(OrbitalPeriod.URANUS.factor);
    }

    double onNeptune() {
        return calculateAge(OrbitalPeriod.NEPTUNE.factor);
    }
}