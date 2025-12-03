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
    const openBrackets = '{[(';

    for (let i = 0; i < this.input.length; i++) {
      const char = this.input[i];

      if (openBrackets.includes(char)) {
        stack.push(char);
      } else if (bracketPairs[char]) {
        if (stack.length === 0 || bracketPairs[char] !== stack.pop()) {
          return false;
        }
      }
    }

    return stack.length === 0;
  }
}