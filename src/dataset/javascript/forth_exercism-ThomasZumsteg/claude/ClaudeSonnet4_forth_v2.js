function n_args(n, func) {
  return function(stack) {
    const stackLen = stack.length;
    if (stackLen < n)
      throw new Error("Stack empty");
    const args = stack.splice(stackLen - n, n);
    const result = func(...args);
    if (result.length > 0) {
      stack.push(...result);
    }
  }
}

export default class Forth {
  constructor() {
    this.stack = [];
    this.env = {};
    this.builtin = {
      "+": n_args(2, (a, b) => [a+b]),
      "-": n_args(2, (a, b) => [a-b]),
      "*": n_args(2, (a, b) => [a*b]),
      "/": n_args(2, (a, b) => {
        if(b === 0)
          throw new Error("Division by zero");
        return [Math.floor(a/b)];
      }),
      "dup": n_args(1, a => [a, a]),
      "drop": n_args(1, () => []),
      "swap": n_args(2, (a, b) => [b, a]),
      "over": n_args(2, (a, b) => [a, b, a]),
    }
  }
  
  evaluate(line) {
    if (line.startsWith(': ') && line.endsWith(' ;')){
      const tokens = line.slice(2, -2).split(" ");
      const head = tokens[0].toLowerCase();
      if(!isNaN(head))
        throw new Error("Invalid definition");
      this.env[head] = tokens.slice(1);
      return;
    }

    const tokens = line.split(" ");
    let i = 0;
    while(i < tokens.length) {
      const token = tokens[i++].toLowerCase();
      const num = Number(token);
      if(!isNaN(num)) {
        this.stack.push(num);
      } else if(token in this.env) {
        tokens.splice(i, 0, ...this.env[token]);
      } else if(token in this.builtin) {
        this.builtin[token](this.stack);
      } else {
        throw new Error('Unknown command');
      }
    }
  }
}