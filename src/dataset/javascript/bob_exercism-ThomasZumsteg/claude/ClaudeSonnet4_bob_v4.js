var Bob = function() {};

Bob.prototype.hey = function(input) {
	var trimmed = input.trim();
	
	if (!trimmed) {
		return "Fine. Be that way!";
	}
	
	var isQuestion = input.charCodeAt(input.length - 1) === 63;
	var hasLetters = false;
	var isAllUpper = true;
	
	for (var i = 0; i < input.length; i++) {
		var code = input.charCodeAt(i);
		if (code >= 65 && code <= 90) {
			hasLetters = true;
		} else if (code >= 97 && code <= 122) {
			hasLetters = true;
			isAllUpper = false;
		}
	}
	
	if (hasLetters && isAllUpper) {
		return "Whoa, chill out!";
	}
	
	if (isQuestion) {
		return "Sure.";
	}
	
	return "Whatever.";
};

module.exports = Bob;