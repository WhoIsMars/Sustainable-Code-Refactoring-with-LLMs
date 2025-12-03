class SpaceAge {
  private readonly earthYearSeconds = 31557600;
  private readonly earthAge: number;

  private static readonly planetYears = {
    mercury: 0.2408467,
    venus: 0.61519726,
    mars: 1.8808158,
    jupiter: 11.862615,
    saturn: 29.447498,
    uranus: 84.016846,
    neptune: 164.79132
  };

  constructor(public seconds: number) {
    this.earthAge = this.seconds / this.earthYearSeconds;
  }

  private roundToTwoDecimals(value: number): number {
    return Math.round(value * 100) / 100;
  }

  onEarth(): number {
    return this.roundToTwoDecimals(this.earthAge);
  }

  onMercury(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.mercury);
  }

  onVenus(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.venus);
  }

  onMars(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.mars);
  }

  onJupiter(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.jupiter);
  }

  onSaturn(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.saturn);
  }

  onUranus(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.uranus);
  }

  onNeptune(): number {
    return this.roundToTwoDecimals(this.earthAge / SpaceAge.planetYears.neptune);
  }
}

export default SpaceAge;