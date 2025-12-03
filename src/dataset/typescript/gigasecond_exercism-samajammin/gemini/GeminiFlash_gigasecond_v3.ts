export default class Gigasecond {
  private readonly initTimeMs: number;

  constructor(initDate: Date) {
    this.initTimeMs = initDate.getTime();
  }

  date(): Date {
    const gigasecondMs = 1_000_000_000_000;
    return new Date(this.initTimeMs + gigasecondMs);
  }
}