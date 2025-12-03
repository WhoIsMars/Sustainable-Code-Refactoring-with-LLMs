class Clock {
  private _hour: number;
  private _minute: number;

  constructor(hour: number, minute: number = 0) {
    const totalMinutes = (hour * 60 + minute) % 1440;
    this._hour = ((Math.floor(totalMinutes / 60) + 24) % 24);
    this._minute = ((totalMinutes % 60) + 60) % 60;
  }

  private static twoDigitString(num: number): string {
    return num < 10 ? `0${num}` : `${num}`;
  }

  public toString(): string {
    return `${Clock.twoDigitString(this._hour)}:${Clock.twoDigitString(this._minute)}`;
  }

  public plus(minutes: number): Clock {
    const totalMinutes = (this._hour * 60 + this._minute + minutes) % 1440;
    this._hour = ((Math.floor(totalMinutes / 60) + 24) % 24);
    this._minute = ((totalMinutes % 60) + 60) % 60;
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