class Clock {
  private _hour: number;
  private _minute: number;

  constructor(hour: number, minute: number = 0) {
    let totalMinutes = hour * 60 + minute;
    totalMinutes = ((totalMinutes % 1440) + 1440) % 1440;
    this._hour = Math.floor(totalMinutes / 60);
    this._minute = totalMinutes % 60;
  }

  private numberToTwoDigitString(num: number): string {
    return num < 10 ? `0${num}` : num.toString();
  }

  public toString(): string {
    return `${this.numberToTwoDigitString(this._hour)}:${this.numberToTwoDigitString(this._minute)}`;
  }

  public plus(minutes: number): Clock {
    let totalMinutes = this._hour * 60 + this._minute + minutes;
    totalMinutes = ((totalMinutes % 1440) + 1440) % 1440;
    this._hour = Math.floor(totalMinutes / 60);
    this._minute = totalMinutes % 60;
    return this;
  }

  public minus(minutes: number): Clock {
    return this.plus(-minutes);
  }

  public equals(clock2: Clock): boolean {
    return this._hour === clock2._hour && this._minute === clock2._minute;
  }
}

export default Clock;