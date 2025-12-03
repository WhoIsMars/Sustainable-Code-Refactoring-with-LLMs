export default class {
  private static readonly COMMANDS = ['wink', 'double blink', 'close your eyes', 'jump'] as const;
  private static readonly REVERSE_FLAG = 16;

  constructor(private _secret: number) {}

  public commands(): string[] {
    const steps: string[] = [];
    let secret = this._secret;
    
    for (let i = 0; i < 4; i++) {
      if (secret & 1) {
        steps.push(this.constructor.COMMANDS[i]);
      }
      secret >>= 1;
    }
    
    return secret & 1 ? steps.reverse() : steps;
  }
}