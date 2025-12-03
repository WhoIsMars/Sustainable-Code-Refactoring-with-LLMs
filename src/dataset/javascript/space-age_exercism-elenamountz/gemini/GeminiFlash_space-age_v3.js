export class SpaceAge {
  constructor(seconds) {
    this.seconds = seconds;
    this.earthYears = seconds / 31557600;
  }

  calculateEarth() {
    return this.earthYears;
  }

  onEarth() {
    return this.roundToTwo(this.earthYears);
  }

  onMercury() {
    return this.roundToTwo(this.earthYears / 0.2408467);
  }

  onVenus() {
    return this.roundToTwo(this.earthYears / 0.61519726);
  }

  onMars() {
    return this.roundToTwo(this.earthYears / 1.8808158);
  }

  onJupiter() {
    return this.roundToTwo(this.earthYears / 11.862615);
  }

  onSaturn() {
    return this.roundToTwo(this.earthYears / 29.447498);
  }

  onUranus() {
    return this.roundToTwo(this.earthYears / 84.016846);
  }

  onNeptune() {
    return this.roundToTwo(this.earthYears / 164.79132);
  }

  roundToTwo(num) {
    return Math.round(num * 100) / 100;
  }
}