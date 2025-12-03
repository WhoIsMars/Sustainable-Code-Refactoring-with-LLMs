export default class Gigasecond {
  private _startMilliseconds: number;

  constructor(start: Date) {
    this._startMilliseconds = start.getTime();
  }

  public date(): Date {
    return new Date(this._startMilliseconds + 1000000000000);
  }
}