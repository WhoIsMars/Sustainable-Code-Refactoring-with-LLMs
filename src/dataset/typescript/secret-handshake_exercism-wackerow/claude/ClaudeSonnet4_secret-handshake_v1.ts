export default class {
  constructor(private _secret: number) {}

  public commands(): string[] {
    const steps: string[] = [];
    const secret = this._secret;
    
    if (secret & 1) steps.push('wink');
    if (secret & 2) steps.push('double blink');
    if (secret & 4) steps.push('close your eyes');
    if (secret & 8) steps.push('jump');
    
    return secret & 16 ? steps.reverse() : steps;
  }
}