function n_args(n, func) {
  return function(stack) {
    if (stack.length < n) {
      throw new Error("Stack empty");
    }
    const args = stack.splice(stack.length - n, n);
    stack.push(...func(...args));
  };
}

export default class Forth {
  constructor() {
    this.stack = [];
    this.env = Object.create(null);
    this.builtin = {
      "+": n_args(2, (a, b) => [a + b]),
      "-": n_args(2, (a, b) => [a - b]),
      "*": n_args(2, (a, b) => [a * b]),
      "/": n_args(2, (a, b) => {
        if (b === 0) {
          throw new Error("Division by zero");
        }
        return [Math.trunc(a / b)];
      }),
      "dup": n_args(1, a => [a, a]),
      "drop": n_args(1, () => []),
      "swap": n_args(2, (a, b) => [b, a]),
      "over": n_args(2, (a, b) => [a, b, a]),
    };
  }

  evaluate(line) {
    if (line.startsWith(': ') && line.endsWith(' ;')) {
      const definition = line.slice(2, -2);
      const tokens = definition.split(" ");
      const head = tokens[0].toLowerCase();

      if (!isNaN(Number(head))) {
        throw new Error("Invalid definition");
      }

      this.env[head] = tokens.slice(1);
      return;
    }

    const tokens = line.split(" ");
    for (let i = 0; i < tokens.length; i++) {
      const token = tokens[i].toLowerCase();

      if (!isNaN(Number(token))) {
        this.stack.push(Number(token));
      } else if (this.env[token]) {
        tokens.splice(i + 1, 0, ...this.env[token]);
      } else if (this.builtin[token]) {
        this.builtin[token](this.stack);
      } else {
        throw new Error('Unknown command');
      }
    }
  }
}