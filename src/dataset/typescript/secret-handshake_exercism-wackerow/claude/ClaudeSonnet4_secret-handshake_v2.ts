export default class {
  constructor(private _secret: number) {}

  public commands(): string[] {
    const steps: string[] = [];
    const commands = ['wink', 'double blink', 'close your eyes', 'jump'];
    
    for (let i = 0; i < 4; i++) {
      if (this._secret & (1 << i)) {
        steps.push(commands[i]);
      }
    }
    
    return this._secret & 16 ? steps.reverse() : steps;
  }
}