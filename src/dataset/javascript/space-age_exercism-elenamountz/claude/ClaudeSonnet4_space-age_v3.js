export class SpaceAge {
  static EARTH_YEAR_SECONDS = 31557600;
  static PLANET_RATIOS = {
    mercury: 0.2408467,
    venus: 0.61519726,
    mars: 1.8808158,
    jupiter: 11.862615,
    saturn: 29.447498,
    uranus: 84.016846,
    neptune: 164.79132
  };

  constructor(seconds) {
    this.earthYears = seconds / SpaceAge.EARTH_YEAR_SECONDS;
  }

  calculateEarth() {
    return this.earthYears;
  }

  onEarth() {
    return Math.round(this.earthYears * 100) / 100;
  }

  onMercury() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.mercury) * 100) / 100;
  }

  onVenus() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.venus) * 100) / 100;
  }

  onMars() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.mars) * 100) / 100;
  }

  onJupiter() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.jupiter) * 100) / 100;
  }

  onSaturn() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.saturn) * 100) / 100;
  }

  onUranus() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.uranus) * 100) / 100;
  }

  onNeptune() {
    return Math.round((this.earthYears / SpaceAge.PLANET_RATIOS.neptune) * 100) / 100;
  }
}