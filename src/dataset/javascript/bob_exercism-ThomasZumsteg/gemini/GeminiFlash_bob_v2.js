var Bob = function() {};

Bob.prototype.hey = function(input) {
    input = input.trim();

    if (!input) {
        return "Fine. Be that way!";
    }

    const isUpperCase = input === input.toUpperCase();
    const hasLetters = /[A-Za-z]/.test(input);

    if (isUpperCase && hasLetters) {
        return "Whoa, chill out!";
    }

    if (input.endsWith("?")) {
        return "Sure.";
    }

    return "Whatever.";
};

module.exports = Bob;