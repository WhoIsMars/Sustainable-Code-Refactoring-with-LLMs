function primeFactors(remainder) {
  /* Finds all prime factors of a number */
  // Finds factors smallest to largest adding to the list of factors
  if (remainder <= 1) {
    return [];
  }

  const factors = [];
  while (remainder % 2 === 0) {
    factors.push(2);
    remainder /= 2;
  }

  let factor = 3;
  const limit = Math.sqrt(remainder);
  while (factor <= limit) {
    while (remainder % factor === 0) {
      factors.push(factor);
      remainder /= factor;
    }
    factor += 2;
  }

  if (remainder > 1) {
    factors.push(remainder);
  }

  return factors;
}

module.exports = { for: primeFactors };