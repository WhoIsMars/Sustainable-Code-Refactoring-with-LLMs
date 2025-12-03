export default class {
  private static readonly COMMANDS = ['wink', 'double blink', 'close your eyes', 'jump'] as const;
  private static readonly REVERSE_FLAG = 16;

  constructor(private _secret: number) {}

  public commands(): string[] {
    const steps: string[] = [];
    let mask = 1;
    
    for (let i = 0; i < 4; i++) {
      if (this._secret & mask) {
        steps.push(HandshakeOptimized.COMMANDS[i]);
      }
      mask <<= 1;
    }
    
    return (this._secret & HandshakeOptimized.REVERSE_FLAG) ? steps.reverse() : steps;
  }
}