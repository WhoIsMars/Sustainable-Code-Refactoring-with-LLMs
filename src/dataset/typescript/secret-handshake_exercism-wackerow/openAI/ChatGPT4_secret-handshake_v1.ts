export default class {
  constructor(private _secret: number) {}

  public commands(): string[] {
    const actions = ['wink', 'double blink', 'close your eyes', 'jump'];
    const steps = actions.filter((_, i) => (this._secret >> i) & 1);
    return (this._secret & 16) ? steps.reverse() : steps;
  }
}