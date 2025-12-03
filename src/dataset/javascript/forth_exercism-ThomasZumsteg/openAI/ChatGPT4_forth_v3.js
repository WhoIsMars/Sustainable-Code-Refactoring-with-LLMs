function n_args(n, func) {
  return function (stack) {
    if (stack.length < n) throw new Error("Stack empty");
    const args = stack.splice(-n);
    const result = func(...args);
    if (result) stack.push(...result);
  };
}

export default class Forth {
  constructor() {
    this.stack = [];
    this.env = {};
    const safeMath = (op) => (a, b) => {
      if (op === "/" && b === 0) throw new Error("Division by zero");
      return [Math.floor(op === "/" ? a / b : op === "+" ? a + b : op === "-" ? a - b : a * b)];
    };
    this.builtin = {
      "+": n_args(2, safeMath("+")),
      "-": n_args(2, safeMath("-")),
      "*": n_args(2, safeMath("*")),
      "/": n_args(2, safeMath("/")),
      "dup": n_args(1, (a) => [a, a]),
      "drop": n_args(1, () => null),
      "swap": n_args(2, (a, b) => [b, a]),
      "over": n_args(2, (a, b) => [a, b, a]),
    };
  }

  evaluate(line) {
    if (line.startsWith(": ") && line.endsWith(" ;")) {
      const tokens = line.slice(2, -2).split(" ");
      const [head, ...body] = tokens;
      if (!isNaN(head)) throw new Error("Invalid definition");
      this.env[head.toLowerCase()] = body;
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