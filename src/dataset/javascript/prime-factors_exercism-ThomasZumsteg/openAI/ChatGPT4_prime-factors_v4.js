function primeFactors(remainder) {
    const factors = [];
    let factor = 2;

    while (remainder % factor === 0) {
        factors.push(factor);
        remainder /= factor;
    }

    factor = 3;
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