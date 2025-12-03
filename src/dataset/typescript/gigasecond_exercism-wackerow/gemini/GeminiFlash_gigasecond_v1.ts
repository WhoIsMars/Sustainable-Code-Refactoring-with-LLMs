export default class Gigasecond {
  private _startEpochMilliseconds: number;

  constructor(start: Date) {
    this._startEpochMilliseconds = start.getTime();
  }

  public date(): Date {
    return new Date(this._startEpochMilliseconds + 1000000000000);
  }
}