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

        private final double value;

        OrbitalPeriod(double value) {
            this.value = value;
        }

        double toEarthYears(double seconds) {
            return seconds / (value * EARTH_ORBITAL_PERIOD);
        }
    }

    SpaceAge(double seconds) {
        this.seconds = seconds;
    }

    double onEarth() {
        return seconds / EARTH_ORBITAL_PERIOD;
    }

    double onMercury() {
        return OrbitalPeriod.MERCURY.toEarthYears(seconds);
    }

    double onVenus() {
        return OrbitalPeriod.VENUS.toEarthYears(seconds);
    }

    double onMars() {
        return OrbitalPeriod.MARS.toEarthYears(seconds);
    }

    double onJupiter() {
        return OrbitalPeriod.JUPITER.toEarthYears(seconds);
    }

    double onSaturn() {
        return OrbitalPeriod.SATURN.toEarthYears(seconds);
    }

    double onUranus() {
        return OrbitalPeriod.URANUS.toEarthYears(seconds);
    }

    double onNeptune() {
        return OrbitalPeriod.NEPTUNE.toEarthYears(seconds);
    }
}