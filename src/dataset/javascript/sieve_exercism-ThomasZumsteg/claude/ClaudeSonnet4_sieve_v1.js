var Sieve = function(size) {
	/* Finds prime numbers */
	
	if (size < 2) {
		this.primes = [];
		return;
	}
	
	this.primes = [2];
	
	// Use typed array for better memory efficiency and performance
	var sieve = new Uint8Array(size + 1);
	sieve.fill(1);
	sieve[0] = sieve[1] = 0;
	
	var sqrtSize = Math.sqrt(size);
	
	for(var n = 3; n <= sqrtSize; n += 2) {
		if(sieve[n]) {
			// Start from n*n and increment by 2*n to skip even multiples
			for(var m = n * n; m <= size; m += 2 * n) {
				sieve[m] = 0;
			}
		}
	}
	
	// Collect remaining primes
	for(var i = 3; i <= size; i += 2) {
		if(sieve[i]) {
			this.primes.push(i);
		}
	}
}

module.exports = Sieve;