const bracket_pairs = new Set(["{}", "[]", "()"]);

function bracket(brackets) {
  const stack = [];
  for (const letter of brackets) {
    if ("{[(".includes(letter)) {
      stack.push(letter);
    } else {
      const last = stack.pop();
      if (!last || !bracket_pairs.has(last + letter)) {
        return false;
      }
    }
  }
  return stack.length === 0;
}

module.exports = bracket;