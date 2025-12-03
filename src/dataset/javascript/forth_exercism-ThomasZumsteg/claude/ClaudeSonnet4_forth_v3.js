function n_args(n, func) {
  return function(stack) {
    if (stack.length < n)
      throw new Error("Stack empty");
    const args = stack.splice(-n);
    const result = func(...args);
    if (result.length > 0) {
      stack.push(...result);
    }
  }
}

export default class Forth {
  constructor() {
    this.stack = [];
    this.env = new Map();
    this.builtin = new Map([
      ["+", n_args(2, (a, b) => [a + b])],
      ["-", n_args(2, (a, b) => [a - b])],
      ["*", n_args(2, (a, b) => [a * b])],
      ["/", n_args(2, (a, b) => {
        if (b === 0)
          throw new Error("Division by zero");
        return [Math.floor(a / b)];
      })],
      ["dup", n_args(1, a => [a, a])],
      ["drop", n_args(1, () => [])],
      ["swap", n_args(2, (a, b) => [b, a])],
      ["over", n_args(2, (a, b) => [a, b, a])]
    ]);
    this.numberRegex = /^-?\d+$/;
  }

  evaluate(line) {
    if (line.startsWith(': ') && line.endsWith(' ;')) {
      const tokens = line.slice(2, -2).split(" ");
      const head = tokens[0].toLowerCase();
      if (this.numberRegex.test(head))
        throw new Error("Invalid definition");
      this.env.set(head, tokens.slice(1));
      return;
    }

    const tokens = line.split(" ");
    let i = 0;
    
    while (i < tokens.length) {
      const token = tokens[i].toLowerCase();
      
      if (this.numberRegex.test(token)) {
        this.stack.push(parseInt(token, 10));
      } else if (this.env.has(token)) {
        tokens.splice(i, 1, ...this.env.get(token));
        continue;
      } else if (this.builtin.has(token)) {
        this.builtin.get(token)(this.stack);
      } else {
        throw new Error('Unknown command');
      }
      i++;
    }
  }
}