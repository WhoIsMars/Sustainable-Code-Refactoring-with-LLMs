class Bob {
  hey(input) {
    input = input.trim();
    if (input === '') return "Fine. Be that way!";
    if (input === input.toUpperCase() && /[A-Z]/.test(input)) return "Whoa, chill out!";
    if (input.endsWith('?')) return "Sure.";
    return "Whatever.";
  }
}

module.exports = Bob;