export default class SecretHandshake {
  constructor(private _secret: number) {}

  public commands(): string[] {
    const steps: string[] = [];
    if (this._secret & 1) {
      steps.push('wink');
    }
    if (this._secret & 2) {
      steps.push('double blink');
    }
    if (this._secret & 4) {
      steps.push('close your eyes');
    }
    if (this._secret & 8) {
      steps.push('jump');
    }
    if (this._secret & 16) {
      steps.reverse();
    }
    return steps;
  }
}