var bracket_pairs = {"{": "}", "[":"]", "(":")"};

function bracket(brackets) {
	/* checks that bracket syntax is correct */
  var stack = [];
  var length = brackets.length;
  
  for(var i = 0; i < length; i++) {
    var letter = brackets[i];
    var closing = bracket_pairs[letter];
    
    if(closing) {
      stack.push(closing);
    } else if(stack.length > 0 && stack[stack.length - 1] === letter) {
      stack.pop();
    } else {
      return false;
    }
  }
  return stack.length === 0;
};

module.exports = bracket;