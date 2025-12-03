var Bob = function() {};

Bob.prototype.hey = function(input) {
  const trimmedInput = input.trim();

  if (!trimmedInput) {
    return "Fine. Be that way!";
  }

  const isUpperCase = trimmedInput === trimmedInput.toUpperCase();
  const hasLetters = /[A-Z]/.test(trimmedInput);
  const isQuestion = trimmedInput.endsWith("?");

  if (isUpperCase && hasLetters) {
    return "Whoa, chill out!";
  }

  if (isQuestion) {
    return "Sure.";
  }

  return "Whatever.";
};

module.exports = Bob;