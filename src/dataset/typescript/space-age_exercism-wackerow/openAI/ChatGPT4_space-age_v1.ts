class SpaceAge {
  private readonly earthYearSeconds = 31557600;
  private readonly orbitalPeriods = {
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

  private calculateAge(planet: keyof typeof this.orbitalPeriods): number {
    return Math.round((this.seconds / this.earthYearSeconds / this.orbitalPeriods[planet]) * 100) / 100;
  }

  onEarth(): number {
    return this.calculateAge("Earth");
  }

  onMercury(): number {
    return this.calculateAge("Mercury");
  }

  onVenus(): number {
    return this.calculateAge("Venus");
  }

  onMars(): number {
    return this.calculateAge("Mars");
  }

  onJupiter(): number {
    return this.calculateAge("Jupiter");
  }

  onSaturn(): number {
    return this.calculateAge("Saturn");
  }

  onUranus(): number {
    return this.calculateAge("Uranus");
  }

  onNeptune(): number {
    return this.calculateAge("Neptune");
  }
}

export default SpaceAge;