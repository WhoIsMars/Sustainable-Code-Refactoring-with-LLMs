export default class Gigasecond {
  private static readonly GIGASECOND_MS = 1e12;

  constructor(private readonly _start: Date) {}

  public date(): Date {
    return new Date(this._start.getTime() + Gigasecond.GIGASECOND_MS);
  }
}