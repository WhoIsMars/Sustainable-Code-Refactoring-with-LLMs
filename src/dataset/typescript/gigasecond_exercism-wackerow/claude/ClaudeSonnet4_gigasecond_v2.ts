export default class Gigasecond {
  private _gigasecondDate: Date;

  constructor(start: Date) {
    this._gigasecondDate = new Date(start.valueOf() + 1e12);
  }

  public date(): Date {
    return this._gigasecondDate;
  }
}