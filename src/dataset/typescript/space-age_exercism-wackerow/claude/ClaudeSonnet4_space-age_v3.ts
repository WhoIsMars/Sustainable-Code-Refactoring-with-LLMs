class SpaceAge {
  private static readonly EARTH_YEAR_SECONDS = 31557600;
  private static readonly PLANET_RATIOS = {
    mercury: 0.2408467,
    venus: 0.61519726,
    mars: 1.8808158,
    jupiter: 11.862615,
    saturn: 29.447498,
    uranus: 84.016846,
    neptune: 164.79132
  } as const;

  private earthAge: number;

  constructor(public seconds: number) {
    this.earthAge = this.seconds / SpaceAge.EARTH_YEAR_SECONDS;
  }

  onEarth(): number {
    return Math.round(this.earthAge * 100) / 100;
  }

  onMercury(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.mercury) * 100) / 100;
  }

  onVenus(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.venus) * 100) / 100;
  }

  onMars(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.mars) * 100) / 100;
  }

  onJupiter(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.jupiter) * 100) / 100;
  }

  onSaturn(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.saturn) * 100) / 100;
  }

  onUranus(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.uranus) * 100) / 100;
  }

  onNeptune(): number {
    return Math.round((this.earthAge / SpaceAge.PLANET_RATIOS.neptune) * 100) / 100;
  }
}

export default SpaceAge;