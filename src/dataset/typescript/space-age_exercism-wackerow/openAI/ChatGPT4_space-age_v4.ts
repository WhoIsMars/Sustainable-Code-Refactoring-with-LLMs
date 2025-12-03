class SpaceAge {
  private static readonly EARTH_YEAR_SECONDS = 31557600;
  private static readonly ORBITAL_PERIODS = {
    Earth: 1,
    Mercury: 0.2408467,
    Venus: 0.61519726,
    Mars: 1.8808158,
    Jupiter: 11.862615,
    Saturn: 29.447498,
    Uranus: 84.016846,
    Neptune: 164.79132,
  };

  constructor(public seconds: number) {}

  private calculateAge(orbitalPeriod: number): number {
    return Math.round((this.seconds / (SpaceAge.EARTH_YEAR_SECONDS * orbitalPeriod)) * 100) / 100;
  }

  onEarth(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Earth);
  }

  onMercury(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Mercury);
  }

  onVenus(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Venus);
  }

  onMars(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Mars);
  }

  onJupiter(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Jupiter);
  }

  onSaturn(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Saturn);
  }

  onUranus(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Uranus);
  }

  onNeptune(): number {
    return this.calculateAge(SpaceAge.ORBITAL_PERIODS.Neptune);
  }
}

export default SpaceAge;