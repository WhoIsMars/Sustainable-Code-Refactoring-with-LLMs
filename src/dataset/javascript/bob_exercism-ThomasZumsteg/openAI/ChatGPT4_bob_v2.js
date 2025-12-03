class Bob {
  hey(input) {
    input = input.trim();
    if (input === '') return "Fine. Be that way!";
    const isShouting = input === input.toUpperCase() && /[A-Z]/.test(input);
    const isQuestion = input.endsWith('?');
    if (isShouting) return "Whoa, chill out!";
    if (isQuestion) return "Sure.";
    return "Whatever.";
  }
}

module.exports = Bob;