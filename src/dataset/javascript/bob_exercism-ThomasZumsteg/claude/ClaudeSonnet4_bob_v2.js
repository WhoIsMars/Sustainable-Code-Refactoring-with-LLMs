var Bob = function() {};

Bob.prototype.hey = function(input) {
	// Cache trimmed input to avoid multiple operations
	var trimmed = input.trim();
	
	// Nothing (empty or whitespace only)
	if (!trimmed)
		return "Fine. Be that way!";
	
	var isQuestion = trimmed.charAt(trimmed.length - 1) === '?';
	var hasLetters = /[A-Za-z]/.test(trimmed);
	var isUpperCase = hasLetters && trimmed === trimmed.toUpperCase();
	
	// Shouting (all upper case with letters)
	if (isUpperCase)
		return "Whoa, chill out!";
	
	// Question (ends with a question mark)
	if (isQuestion)
		return "Sure.";
	
	// Default
	return "Whatever.";
};

module.exports = Bob;