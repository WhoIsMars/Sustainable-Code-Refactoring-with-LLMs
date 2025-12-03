class SpaceAge {
  private static readonly earthYearSeconds = 31557600;
  private static readonly orbitalPeriods = {
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
    return Math.round((this.seconds / (SpaceAge.earthYearSeconds * orbitalPeriod)) * 100) / 100;
  }

  onEarth(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Earth);
  }

  onMercury(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Mercury);
  }

  onVenus(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Venus);
  }

  onMars(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Mars);
  }

  onJupiter(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Jupiter);
  }

  onSaturn(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Saturn);
  }

  onUranus(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Uranus);
  }

  onNeptune(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.Neptune);
  }
}

export default SpaceAge;