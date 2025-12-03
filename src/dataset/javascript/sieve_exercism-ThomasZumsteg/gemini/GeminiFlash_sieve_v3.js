var Sieve = function(size) {
	this.primes = [];
	if (size < 2) {
		return;
	}

	const sieve = new Array(size + 1);
	sieve.fill(true);

	sieve[0] = sieve[1] = false;

	for (let p = 2; p * p <= size; p++) {
		if (sieve[p]) {
			for (let i = p * p; i <= size; i += p) {
				sieve[i] = false;
			}
		}
	}

	for (let p = 2; p <= size; p++) {
		if (sieve[p]) {
			this.primes.push(p);
		}
	}
};

module.exports = Sieve;