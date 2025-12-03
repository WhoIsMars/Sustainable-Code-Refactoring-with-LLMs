var Sieve = function(size) {
	this.primes = [];
	if (size < 2) return;

	const sieve = new Uint8Array(size + 1);
	sieve[2] = 1;
	this.primes.push(2);

	for (let n = 3; n <= size; n += 2) {
		if (!sieve[n]) {
			this.primes.push(n);
			for (let m = n * n; m <= size; m += n * 2) {
				sieve[m] = 1;
			}
		}
	}
};

module.exports = Sieve;