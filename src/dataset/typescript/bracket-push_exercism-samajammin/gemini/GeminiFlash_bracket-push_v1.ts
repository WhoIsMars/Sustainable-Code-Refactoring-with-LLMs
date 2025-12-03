export default class BracketPush {
  private readonly input: string;

  constructor(input: string) {
    this.input = input;
  }

  isPaired(): boolean {
    const stack: string[] = [];
    const bracketPairs = new Map<string, string>([
      ['}', '{'],
      [']', '['],
      [')', '('],
    ]);
    const openBrackets = new Set(['{', '[', '(']);

    for (let i = 0; i < this.input.length; i++) {
      const char = this.input[i];

      if (openBrackets.has(char)) {
        stack.push(char);
      } else {
        const matchingBracket = bracketPairs.get(char);
        if (matchingBracket) {
          if (stack.length > 0 && stack[stack.length - 1] === matchingBracket) {
            stack.pop();
          } else {
            return false;
          }
        }
      }
    }

    return stack.length === 0;
  }
}