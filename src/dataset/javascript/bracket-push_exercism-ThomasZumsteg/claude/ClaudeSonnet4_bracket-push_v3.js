const bracket_pairs = {"{": "}", "[": "]", "(": ")"};

function bracket(brackets) {
  const stack = [];
  
  for (let i = 0; i < brackets.length; i++) {
    const char = brackets[i];
    const closingBracket = bracket_pairs[char];
    
    if (closingBracket) {
      stack.push(closingBracket);
    } else if (stack.length > 0 && stack[stack.length - 1] === char) {
      stack.pop();
    } else {
      return false;
    }
  }
  
  return stack.length === 0;
}

module.exports = bracket;