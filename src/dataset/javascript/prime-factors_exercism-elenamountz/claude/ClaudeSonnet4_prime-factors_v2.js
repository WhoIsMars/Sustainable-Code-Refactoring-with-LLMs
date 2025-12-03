export const primeFactors = (number) => {
  const factors = [];
  
  // Handle factor 2 separately to allow odd-only iteration
  while (number % 2 === 0) {
    factors.push(2);
    number /= 2;
  }
  
  // Only check odd divisors up to sqrt(number)
  for (let divisor = 3; divisor * divisor <= number; divisor += 2) {
    while (number % divisor === 0) {
      factors.push(divisor);
      number /= divisor;
    }
  }
  
  // If number > 1, then it's a prime factor
  if (number > 1) {
    factors.push(number);
  }
  
  return factors;
};