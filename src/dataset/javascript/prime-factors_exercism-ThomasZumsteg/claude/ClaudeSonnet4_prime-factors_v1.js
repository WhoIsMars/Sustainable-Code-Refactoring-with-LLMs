function primeFactors(remainder) {
	/* Finds all prime factors of a number */
	// Finds factors smallest to largest adding to the list of factors
	var factors = [];
	
	// Handle factor 2 separately
	while(remainder % 2 === 0) {
		factors.push(2);
		remainder >>>= 1; // Bit shift division by 2
	}
	
	// Check odd factors starting from 3
	var factor = 3;
	var limit = Math.sqrt(remainder);
	while(factor <= limit) {
		while(remainder % factor === 0) {
			factors.push(factor);
			remainder /= factor;
			limit = Math.sqrt(remainder); // Update limit as remainder shrinks
		}
		factor += 2; // Skip even numbers
	}
	
	if(remainder > 1)
		factors.push(remainder);
	return factors;
}

module.exports = {for: primeFactors};