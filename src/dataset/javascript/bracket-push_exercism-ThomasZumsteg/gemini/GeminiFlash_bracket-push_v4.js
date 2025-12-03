var bracket_pairs = {"{": "}", "[":"]", "(":")"};

function bracket(brackets) {
  var stack = [];
  for (var i = 0; i < brackets.length; i++) {
    var letter = brackets[i];
    var expected = bracket_pairs[letter];
    if (expected) {
      stack.push(expected);
    } else if (stack.length > 0 && stack[stack.length - 1] === letter) {
      stack.pop();
    } else {
      return false;
    }
  }
  return stack.length === 0;
};

module.exports = bracket;