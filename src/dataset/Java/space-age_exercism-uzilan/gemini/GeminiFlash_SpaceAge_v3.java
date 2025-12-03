class SpaceAge {

    private final double seconds;
    private static final double EARTH_ORBITAL_PERIOD = 31557600.0; // in seconds

    private enum OrbitalPeriod { // in earth years
        MERCURY(0.2408467),
        VENUS(0.61519726),
        MARS(1.8808158),
        JUPITER(11.862615),
        SATURN(29.447498),
        URANUS(84.016846),
        NEPTUNE(164.79132);

        final double value;

        OrbitalPeriod(double value) {
            this.value = value;
        }
    }

    SpaceAge(double seconds) {
        this.seconds = seconds;
    }

    private double inEarthYears(OrbitalPeriod orbitalPeriod) {
        return seconds / (orbitalPeriod.value * EARTH_ORBITAL_PERIOD);
    }

    double onEarth() {
        return seconds / EARTH_ORBITAL_PERIOD;
    }

    double onMercury() {
        return seconds / (OrbitalPeriod.MERCURY.value * EARTH_ORBITAL_PERIOD);
    }

    double onVenus() {
        return seconds / (OrbitalPeriod.VENUS.value * EARTH_ORBITAL_PERIOD);
    }

    double onMars() {
        return seconds / (OrbitalPeriod.MARS.value * EARTH_ORBITAL_PERIOD);
    }

    double onJupiter() {
        return seconds / (OrbitalPeriod.JUPITER.value * EARTH_ORBITAL_PERIOD);
    }

    double onSaturn() {
        return seconds / (OrbitalPeriod.SATURN.value * EARTH_ORBITAL_PERIOD);
    }

    double onUranus() {
        return seconds / (OrbitalPeriod.URANUS.value * EARTH_ORBITAL_PERIOD);
    }

    double onNeptune() {
        return seconds / (OrbitalPeriod.NEPTUNE.value * EARTH_ORBITAL_PERIOD);
    }
}