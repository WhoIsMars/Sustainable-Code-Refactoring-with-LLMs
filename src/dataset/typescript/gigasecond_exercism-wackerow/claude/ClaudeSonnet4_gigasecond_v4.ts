export default class Gigasecond {
  private readonly _gigasecondMs: number;

  constructor(private readonly _start: Date) {
    this._gigasecondMs = this._start.valueOf() + 1000000000000;
  }

  public date(): Date {
    return new Date(this._gigasecondMs);
  }
}