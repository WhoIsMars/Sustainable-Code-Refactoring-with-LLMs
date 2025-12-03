export default class BracketPush {
  private static readonly bracketPairs = new Map([
    ['}', '{'],
    [']', '['],
    [')', '(']
  ]);

  constructor(private readonly input: string) {}

  isPaired(): boolean {
    const stack: string[] = [];
    for (const char of this.input) {
      if (BracketPush.bracketPairs.has(char)) {
        if (stack.pop() !== BracketPush.bracketPairs.get(char)) {
          return false;
        }
      } else if (BracketPush.bracketPairs.has([...BracketPush.bracketPairs.values()].find(v => v === char))) {
        stack.push(char);
      }
    }
    return stack.length === 0;
  }
}