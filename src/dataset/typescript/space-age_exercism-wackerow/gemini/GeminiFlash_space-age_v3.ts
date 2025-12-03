class SpaceAge {
  private static readonly earthYearSeconds = 31557600;
  private readonly secondsInEarthYears: number;

  private static readonly orbitalPeriods: { [planet: string]: number } = {
    mercury: 0.2408467,
    venus: 0.61519726,
    mars: 1.8808158,
    jupiter: 11.862615,
    saturn: 29.447498,
    uranus: 84.016846,
    neptune: 164.79132,
  };

  constructor (public seconds: number) {
    this.secondsInEarthYears = seconds / SpaceAge.earthYearSeconds;
  }

  private calculateAge(orbitalPeriod: number): number {
    return Math.round(this.secondsInEarthYears / orbitalPeriod * 100) / 100;
  }

  onEarth(): number {
    return Math.round(this.secondsInEarthYears * 100) / 100;
  }

  onMercury(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.mercury);
  }

  onVenus(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.venus);
  }

  onMars(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.mars);
  }

  onJupiter(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.jupiter);
  }

  onSaturn(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.saturn);
  }

  onUranus(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.uranus);
  }

  onNeptune(): number {
    return this.calculateAge(SpaceAge.orbitalPeriods.neptune);
  }
}

export default SpaceAge;