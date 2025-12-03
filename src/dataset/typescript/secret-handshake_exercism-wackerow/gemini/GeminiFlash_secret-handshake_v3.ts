export default class SecretHandshake {
  private _secret: number;

  constructor(secret: number) {
    this._secret = secret;
  }

  public commands(): string[] {
    const steps: string[] = [];
    if (this._secret & 1) {
      steps.push('wink');
    }
    if ((this._secret >> 1) & 1) {
      steps.push('double blink');
    }
    if ((this._secret >> 2) & 1) {
      steps.push('close your eyes');
    }
    if ((this._secret >> 3) & 1) {
      steps.push('jump');
    }
    if ((this._secret >> 4) & 1) {
      steps.reverse();
    }
    return steps;
  }
}