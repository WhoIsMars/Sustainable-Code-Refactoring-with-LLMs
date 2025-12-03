export default class Gigasecond {
  private readonly _startTime: number;

  constructor(start: Date) {
    this._startTime = start.valueOf();
  }

  public date(): Date {
    return new Date(this._startTime + 1000000000000);
  }
}