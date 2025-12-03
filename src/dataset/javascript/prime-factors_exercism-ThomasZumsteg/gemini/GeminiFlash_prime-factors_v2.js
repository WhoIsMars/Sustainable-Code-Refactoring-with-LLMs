function primeFactors(remainder) {
    /* Finds all prime factors of a number */
    // Finds factors smallest to largest adding to the list of factors
    const factors = [];

    // Optimization: Handle even numbers first
    while (remainder % 2 === 0) {
        factors.push(2);
        remainder /= 2;
    }

    // Optimization: Iterate only through odd numbers
    for (let factor = 3; factor * factor <= remainder; factor += 2) {
        while (remainder % factor === 0) {
            factors.push(factor);
            remainder /= factor;
        }
    }

    // If remainder is still greater than 1, it's a prime factor
    if (remainder > 1) {
        factors.push(remainder);
    }

    return factors;
}

module.exports = { for: primeFactors };