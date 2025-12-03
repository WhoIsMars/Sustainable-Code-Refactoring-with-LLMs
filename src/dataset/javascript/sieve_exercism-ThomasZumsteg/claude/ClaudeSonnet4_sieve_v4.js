var Sieve = function(size) {
	if (size < 2) {
		this.primes = [];
		return;
	}
	
	this.primes = [2];
	var sieve = new Array(size + 1).fill(true);
	sieve[0] = sieve[1] = false;
	
	var limit = Math.sqrt(size);
	
	for (var n = 3; n <= limit; n += 2) {
		if (sieve[n]) {
			for (var m = n * n; m <= size; m += n) {
				sieve[m] = false;
			}
		}
	}
	
	for (var i = 3; i <= size; i += 2) {
		if (sieve[i]) {
			this.primes.push(i);
		}
	}
}

module.exports = Sieve;