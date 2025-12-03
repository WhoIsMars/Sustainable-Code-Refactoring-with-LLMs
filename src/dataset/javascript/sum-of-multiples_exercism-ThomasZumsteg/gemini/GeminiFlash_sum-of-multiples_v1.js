function to(num) {
  let sum = 0;
  for (let n = 0; n < num; n++) {
    for (let i = 0; i < this.factors.length; i++) {
      if (n % this.factors[i] === 0) {
        sum += n;
        break; // Optimization: Once divisible, no need to check other factors
      }
    }
  }
  return sum;
}

module.exports = function(factors) {
  const factorsArray = factors || [3, 5]; // Ensure factors is always an array

  return {
    factors: factorsArray,
    to: to
  };
};