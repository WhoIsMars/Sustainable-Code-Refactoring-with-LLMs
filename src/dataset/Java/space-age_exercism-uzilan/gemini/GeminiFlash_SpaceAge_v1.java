class SpaceAge {

    private final double seconds;
    private static final double EARTH_ORBITAL_PERIOD = 31557600.0;
    private static final double SECONDS_PER_EARTH_YEAR = EARTH_ORBITAL_PERIOD;

    private enum OrbitalPeriod {
        MERCURY(0.2408467),
        VENUS(0.61519726),
        MARS(1.8808158),
        JUPITER(11.862615),
        SATURN(29.447498),
        URANUS(84.016846),
        NEPTUNE(164.79132);

        final double orbitalPeriodInEarthYears;

        OrbitalPeriod(double orbitalPeriodInEarthYears) {
            this.orbitalPeriodInEarthYears = orbitalPeriodInEarthYears;
        }
    }

    SpaceAge(double seconds) {
        this.seconds = seconds;
    }

    private double calculateAge(double orbitalPeriodInEarthYears) {
        return seconds / (SECONDS_PER_EARTH_YEAR * orbitalPeriodInEarthYears);
    }

    double onEarth() {
        return seconds / SECONDS_PER_EARTH_YEAR;
    }

    double onMercury() {
        return calculateAge(OrbitalPeriod.MERCURY.orbitalPeriodInEarthYears);
    }

    double onVenus() {
        return calculateAge(OrbitalPeriod.VENUS.orbitalPeriodInEarthYears);
    }

    double onMars() {
        return calculateAge(OrbitalPeriod.MARS.orbitalPeriodInEarthYears);
    }

    double onJupiter() {
        return calculateAge(OrbitalPeriod.JUPITER.orbitalPeriodInEarthYears);
    }

    double onSaturn() {
        return calculateAge(OrbitalPeriod.SATURN.orbitalPeriodInEarthYears);
    }

    double onUranus() {
        return calculateAge(OrbitalPeriod.URANUS.orbitalPeriodInEarthYears);
    }

    double onNeptune() {
        return calculateAge(OrbitalPeriod.NEPTUNE.orbitalPeriodInEarthYears);
    }
}