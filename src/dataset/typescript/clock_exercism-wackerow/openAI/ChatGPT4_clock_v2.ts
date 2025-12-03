class Clock {
  private _hour: number;
  private _minute: number;

  constructor(hour: number, minute: number = 0) {
    const totalMinutes = (hour * 60 + minute) % 1440;
    this._hour = ((Math.floor(totalMinutes / 60) + 24) % 24);
    this._minute = ((totalMinutes % 60) + 60) % 60;
  }

  private static formatTwoDigits(num: number): string {
    return num.toString().padStart(2, '0');
  }

  public toString(): string {
    return `${Clock.formatTwoDigits(this._hour)}:${Clock.formatTwoDigits(this._minute)}`;
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