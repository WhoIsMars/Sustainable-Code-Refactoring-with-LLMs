export const primeFactors = (number) => {
  const factors = [];
  while (number % 2 === 0) {
    factors.push(2);
    number /= 2;
  }
  for (let divisor = 3; divisor * divisor <= number; divisor += 2) {
    while (number % divisor === 0) {
      factors.push(divisor);
      number /= divisor;
    }
  }
  if (number > 2) factors.push(number);
  return factors;
};