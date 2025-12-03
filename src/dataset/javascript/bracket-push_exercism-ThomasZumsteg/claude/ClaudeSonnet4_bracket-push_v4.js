const bracket_pairs = {"{": "}", "[":"]", "(":")"};
const closing_brackets = new Set(["}", "]", ")"]);

function bracket(brackets) {
  const stack = [];
  
  for (let i = 0; i < brackets.length; i++) {
    const char = brackets[i];
    
    if (bracket_pairs[char]) {
      stack.push(bracket_pairs[char]);
    } else if (closing_brackets.has(char)) {
      if (stack.length === 0 || stack.pop() !== char) {
        return false;
      }
    } else {
      return false;
    }
  }
  
  return stack.length === 0;
}

module.exports = bracket;