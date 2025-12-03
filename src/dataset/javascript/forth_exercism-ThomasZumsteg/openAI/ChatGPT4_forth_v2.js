function n_args(n, func) {
  return function(stack) {
    if (stack.length < n) throw new Error("Stack empty");
    const args = stack.splice(-n);
    const result = func(...args);
    if (result.length) stack.push(...result);
  };
}

export default class Forth {
  constructor() {
    this.stack = [];
    this.env = {};
    const ops = {
      "+": (a, b) => [a + b],
      "-": (a, b) => [a - b],
      "*": (a, b) => [a * b],
      "/": (a, b) => {
        if (b === 0) throw new Error("Division by zero");
        return [Math.floor(a / b)];
      },
      "dup": (a) => [a, a],
      "drop": () => [],
      "swap": (a, b) => [b, a],
      "over": (a, b) => [a, b, a],
    };
    this.builtin = Object.fromEntries(
      Object.entries(ops).map(([key, func]) => [key, n_args(func.length, func)])
    );
  }

  evaluate(line) {
    if (line.startsWith(": ") && line.endsWith(" ;")) {
      const tokens = line.slice(2, -2).split(" ");
      const head = tokens[0].toLowerCase();
      if (!isNaN(head)) throw new Error("Invalid definition");
      this.env[head] = tokens.slice(1);
      return;
    }

    const tokens = line.split(" ");
    for (let i = 0; i < tokens.length; i++) {
      const token = tokens[i].toLowerCase();
      if (!isNaN(token)) {
        this.stack.push(Number(token));
      } else if (token in this.env) {
        tokens.splice(i, 1, ...this.env[token]);
        i--;
      } else if (token in this.builtin) {
        this.builtin[token](this.stack);
      } else {
        throw new Error("Unknown command");
      }
    }
  }
}