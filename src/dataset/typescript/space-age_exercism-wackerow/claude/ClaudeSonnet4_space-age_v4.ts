class SpaceAge {
  private readonly earthYearSeconds = 31557600;
  private readonly earthAgeInYears: number;

  private static readonly planetYearRatios = {
    mercury: 0.2408467,
    venus: 0.61519726,
    mars: 1.8808158,
    jupiter: 11.862615,
    saturn: 29.447498,
    uranus: 84.016846,
    neptune: 164.79132
  } as const;

  constructor(public seconds: number) {
    this.earthAgeInYears = Math.round(this.seconds * 100 / this.earthYearSeconds) / 100;
  }

  private calculatePlanetAge(planetYearRatio: number): number {
    return Math.round(this.earthAgeInYears / planetYearRatio * 100) / 100;
  }

  onEarth(): number {
    return this.earthAgeInYears;
  }

  onMercury(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.mercury);
  }

  onVenus(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.venus);
  }

  onMars(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.mars);
  }

  onJupiter(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.jupiter);
  }

  onSaturn(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.saturn);
  }

  onUranus(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.uranus);
  }

  onNeptune(): number {
    return this.calculatePlanetAge(SpaceAge.planetYearRatios.neptune);
  }
}

export default SpaceAge;