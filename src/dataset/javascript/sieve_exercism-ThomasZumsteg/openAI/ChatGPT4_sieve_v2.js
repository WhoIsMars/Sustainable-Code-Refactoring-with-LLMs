class Sieve {
    constructor(size) {
        this.primes = [];
        if (size < 2) return;

        const sieve = new Uint8Array(size + 1);
        sieve.fill(1);
        sieve[0] = sieve[1] = 0;

        for (let n = 2; n * n <= size; n++) {
            if (sieve[n]) {
                for (let m = n * n; m <= size; m += n) {
                    sieve[m] = 0;
                }
            }
        }

        for (let n = 2; n <= size; n++) {
            if (sieve[n]) this.primes.push(n);
        }
    }
}

module.exports = Sieve;