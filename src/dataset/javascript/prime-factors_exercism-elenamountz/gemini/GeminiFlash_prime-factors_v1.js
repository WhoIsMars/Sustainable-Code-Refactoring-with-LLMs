export const primeFactors = (number) => {
  const factors = [];
  let divisor = 2;
  while (divisor * divisor <= number) {
    while (number % divisor === 0) {
      factors.push(divisor);
      number /= divisor;
    }
    divisor++;
  }
  if (number > 1) {
    factors.push(number);
  }
  return factors;
};