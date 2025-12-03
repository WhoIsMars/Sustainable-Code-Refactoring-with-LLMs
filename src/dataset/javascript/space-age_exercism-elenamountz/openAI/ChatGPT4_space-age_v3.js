export class SpaceAge {
  static EARTH_YEAR_SECONDS = 31557600;
  static ORBITAL_PERIODS = {
    Earth: 1,
    Mercury: 0.2408467,
    Venus: 0.61519726,
    Mars: 1.8808158,
    Jupiter: 11.862615,
    Saturn: 29.447498,
    Uranus: 84.016846,
    Neptune: 164.79132,
  };

  constructor(seconds) {
    this.seconds = seconds;
    this.earthYears = seconds / SpaceAge.EARTH_YEAR_SECONDS;
  }

  #calculateAge(orbitalPeriod) {
    return Math.round((this.earthYears / orbitalPeriod) * 100) / 100;
  }

  onEarth() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Earth);
  }

  onMercury() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Mercury);
  }

  onVenus() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Venus);
  }

  onMars() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Mars);
  }

  onJupiter() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Jupiter);
  }

  onSaturn() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Saturn);
  }

  onUranus() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Uranus);
  }

  onNeptune() {
    return this.#calculateAge(SpaceAge.ORBITAL_PERIODS.Neptune);
  }
}