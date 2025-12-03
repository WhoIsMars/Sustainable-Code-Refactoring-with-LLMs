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
  };

  constructor (public seconds: number) {
    this.earthAgeInYears = this.seconds / this.earthYearSeconds;
  }

  private roundToTwoDecimals(value: number): number {
    return Math.round(value * 100) / 100;
  }

  onEarth(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears);
  }

  onMercury(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.mercury);
  }

  onVenus(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.venus);
  }

  onMars(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.mars);
  }

  onJupiter(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.jupiter);
  }

  onSaturn(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.saturn);
  }

  onUranus(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.uranus);
  }

  onNeptune(): number {
    return this.roundToTwoDecimals(this.earthAgeInYears / SpaceAge.planetYearRatios.neptune);
  }
}

export default SpaceAge;