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
	
	// Only check odd numbers, skip even numbers after 2
	for(var n = 3; n * n <= size; n += 2) {
		if(sieve[n]) {
			// Start marking from n*n, skip even multiples
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