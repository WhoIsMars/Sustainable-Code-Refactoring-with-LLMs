class Clock {
  private _hour: number;
  private _minute: number;

  constructor(hour: number, minute: number = 0) {
    minute = minute % 60;
    if (minute < 0) {
      minute += 60;
    }
    hour = (hour + Math.floor(minute / 60)) % 24;
    if (hour < 0) {
      hour += 24;
    }

    this._minute = minute;
    this._hour = hour;
  }

  private numberToTwoDigitString(num: number): string {
    return num < 10 ? `0${num}` : num.toString();
  }

  public toString(): string {
    return `${this.numberToTwoDigitString(this._hour)}:${this.numberToTwoDigitString(this._minute)}`;
  }

  public plus(minutes: number): Clock {
    let totalMinutes = this._minute + minutes;
    let hourChange = Math.floor(totalMinutes / 60);
    this._minute = totalMinutes % 60;

    if (this._minute < 0) {
      this._minute += 60;
      hourChange--;
    }

    this._hour = (this._hour + hourChange) % 24;
    if (this._hour < 0) {
      this._hour += 24;
    }

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