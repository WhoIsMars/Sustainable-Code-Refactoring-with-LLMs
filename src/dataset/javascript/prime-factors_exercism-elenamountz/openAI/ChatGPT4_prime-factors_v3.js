export const primeFactors = (number) => {
  const factors = [];
  for (let divisor = 2; divisor * divisor <= number; divisor++) {
    while (number % divisor === 0) {
      factors.push(divisor);
      number /= divisor;
    }
  }
  if (number > 1) factors.push(number);
  return factors;
};