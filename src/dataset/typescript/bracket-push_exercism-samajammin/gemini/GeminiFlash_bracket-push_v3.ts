export default class BracketPush {
  readonly input: string;

  constructor(input: string) {
    this.input = input;
  }

  isPaired(): boolean {
    const stack: string[] = [];
    const bracketPairs: { [key: string]: string } = {
      '}': '{',
      ']': '[',
      ')': '('
    };
    const openBrackets = new Set(['{', '[', '(']);

    for (let i = 0; i < this.input.length; i++) {
      const char = this.input[i];

      if (openBrackets.has(char)) {
        stack.push(char);
      } else if (bracketPairs[char]) {
        if (stack.length === 0 || stack[stack.length - 1] !== bracketPairs[char]) {
          return false;
        }
        stack.pop();
      }
    }

    return stack.length === 0;
  }
}