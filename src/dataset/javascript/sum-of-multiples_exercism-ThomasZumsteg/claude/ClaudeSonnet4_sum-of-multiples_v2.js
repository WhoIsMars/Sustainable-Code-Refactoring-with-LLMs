function to(num) {
	let total = 0;
	const factors = this.factors;
	const factorsLength = factors.length;
	
	for (let n = 0; n < num; n++) {
		for (let i = 0; i < factorsLength; i++) {
			if (n % factors[i] === 0) {
				total += n;
				break;
			}
		}
	}
	
	return total;
}

module.exports = function(factors) { 
	return { 
		factors: factors || [3, 5],
		to: to 
	};
};