var Bob = function() {};

Bob.prototype.hey = function(input) {
	var trimmed = input.trim();
	
	if (!trimmed) {
		return "Fine. Be that way!";
	}
	
	var isQuestion = input.charAt(input.length - 1) === '?';
	var hasLetters = /[A-Za-z]/.test(input);
	var isAllUpperCase = hasLetters && input === input.toUpperCase();
	
	if (isAllUpperCase) {
		return "Whoa, chill out!";
	}
	
	if (isQuestion) {
		return "Sure.";
	}
	
	return "Whatever.";
};

module.exports = Bob;