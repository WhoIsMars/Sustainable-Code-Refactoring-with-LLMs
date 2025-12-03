var Sieve = function(size) {
    this.primes = [];
    if (size < 2) return;

    const limit = Math.floor((size - 1) / 2);
    const sieve = new Array(limit + 1).fill(true);

    for (let i = 0; i <= Math.sqrt(size) / 2; i++) {
        if (sieve[i]) {
            let p = 2 * i + 3;
            for (let j = i * (p); j <= limit; j += p) {
                sieve[j] = false;
            }
        }
    }

    this.primes.push(2);
    for (let i = 0; i <= limit; i++) {
        if (sieve[i]) {
            this.primes.push(2 * i + 3);
        }
    }
};

module.exports = Sieve;