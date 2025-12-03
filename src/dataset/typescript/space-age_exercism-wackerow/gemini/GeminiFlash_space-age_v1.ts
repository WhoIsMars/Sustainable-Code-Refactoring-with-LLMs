class SpaceAge {
  private static readonly earthYearSeconds = 31557600;

  private static readonly orbitalPeriods: { [planet: string]: number } = {
    mercury: 0.2408467,
    venus: 0.61519726,
    mars: 1.8808158,
    jupiter: 11.862615,
    saturn: 29.447498,
    uranus: 84.016846,
    neptune: 164.79132,
  };

  private readonly secondsInEarthYears: number;

  constructor (public seconds: number) {
    this.secondsInEarthYears = seconds / SpaceAge.earthYearSeconds;
  }

  onEarth(): number {
    return this.roundToTwo(this.secondsInEarthYears);
  }

  onMercury(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.mercury);
  }
  onVenus(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.venus);
  }
  onMars(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.mars);
  }
  onJupiter(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.jupiter);
  }
  onSaturn(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.saturn);
  }
  onUranus(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.uranus);
  }
  onNeptune(): number {
    return this.roundToTwo(this.secondsInEarthYears / SpaceAge.orbitalPeriods.neptune);
  }

  private roundToTwo(value: number): number {
    return Math.round(value * 100) / 100;
  }
}

export default SpaceAge;