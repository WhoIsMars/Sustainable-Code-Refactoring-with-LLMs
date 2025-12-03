export default class Gigasecond {
  private _startDateMilliseconds: number;

  constructor(start: Date) {
    this._startDateMilliseconds = start.getTime();
  }

  public date(): Date {
    return new Date(this._startDateMilliseconds + 1000000000000);
  }
}