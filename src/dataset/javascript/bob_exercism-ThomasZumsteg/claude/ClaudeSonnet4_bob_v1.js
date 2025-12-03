var Bob = function() {};

Bob.prototype.hey = function(input) {
	var trimmed = input.trim();
	
	if (!trimmed) {
		return "Fine. Be that way!";
	}
	
	var hasLetters = /[A-Za-z]/.test(trimmed);
	var isAllUpperCase = hasLetters && trimmed === trimmed.toUpperCase();
	var isQuestion = trimmed.charCodeAt(trimmed.length - 1) === 63;
	
	if (isAllUpperCase) {
		return "Whoa, chill out!";
	}
	
	if (isQuestion) {
		return "Sure.";
	}
	
	return "Whatever.";
};

module.exports = Bob;