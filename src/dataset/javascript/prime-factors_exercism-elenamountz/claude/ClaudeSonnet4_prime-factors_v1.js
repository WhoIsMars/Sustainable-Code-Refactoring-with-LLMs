export const primeFactors = (number) => {
  if (number <= 1) return [];
  
  const factors = [];
  
  // Handle factor 2 separately to allow skipping even numbers
  while (number % 2 === 0) {
    factors.push(2);
    number /= 2;
  }
  
  // Check odd numbers only, up to sqrt(number)
  for (let divisor = 3; divisor * divisor <= number; divisor += 2) {
    while (number % divisor === 0) {
      factors.push(divisor);
      number /= divisor;
    }
  }
  
  // If number is still > 1, it's a prime factor
  if (number > 1) {
    factors.push(number);
  }
  
  return factors;
};