export const steps = (n) => {
  if (n <= 0) {
    throw new Error('Only positive numbers are allowed');
  }

  let step = 0;
  let number = n;

  while (number !== 1) {
    number = number % 2 === 0 ? number / 2 : (3 * number) + 1;
    step++;
  }

  return step;
};