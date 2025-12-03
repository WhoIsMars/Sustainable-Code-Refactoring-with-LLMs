export default class {
  private readonly _steps = ['wink', 'double blink', 'close your eyes', 'jump'];

  constructor(private _secret: number) {}

  public commands(): string[] {
    const steps: string[] = this._steps.filter((_, i) => (this._secret >> i) & 1);
    return (this._secret & 16) ? steps.reverse() : steps;
  }
}