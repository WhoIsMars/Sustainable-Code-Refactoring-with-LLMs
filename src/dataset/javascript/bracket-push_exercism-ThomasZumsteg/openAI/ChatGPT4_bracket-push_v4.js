const bracket_pairs = new Map([["{", "}"], ["[", "]"], ["(", ")"]]);

function bracket(brackets) {
  const stack = [];
  for (const char of brackets) {
    if (bracket_pairs.has(char)) {
      stack.push(bracket_pairs.get(char));
    } else if (stack.length && stack[stack.length - 1] === char) {
      stack.pop();
    } else {
      return false;
    }
  }
  return stack.length === 0;
}

module.exports = bracket;