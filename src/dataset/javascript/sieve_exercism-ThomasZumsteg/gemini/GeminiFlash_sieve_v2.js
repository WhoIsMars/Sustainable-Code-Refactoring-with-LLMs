var Sieve = function(size) {
    this.primes = [];
    if (size < 2) return;

    const sieve = new Array(size + 1).fill(true);
    sieve[0] = sieve[1] = false;

    for (let p = 2; p <= Math.sqrt(size); p++) {
        if (sieve[p]) {
            for (let i = p * p; i <= size; i += p) {
                sieve[i] = false;
            }
        }
    }

    for (let i = 2; i <= size; i++) {
        if (sieve[i]) {
            this.primes.push(i);
        }
    }
};

module.exports = Sieve;