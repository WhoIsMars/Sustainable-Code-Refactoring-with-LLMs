class Bob {
  hey(input) {
    const trimmedInput = input.trim();
    if (trimmedInput === '') return "Fine. Be that way!";
    if (trimmedInput === trimmedInput.toUpperCase() && /[A-Z]/.test(trimmedInput)) return "Whoa, chill out!";
    if (trimmedInput.endsWith('?')) return "Sure.";
    return "Whatever.";
  }
}

module.exports = Bob;