export default class Gigasecond {
  private readonly _endDate: Date;

  constructor(start: Date) {
    this._endDate = new Date(start.valueOf() + 1e12);
  }

  public date(): Date {
    return this._endDate;
  }
}