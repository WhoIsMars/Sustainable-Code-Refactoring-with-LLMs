export const steps = (n) => {
  if (n <= 0) throw new Error('Only positive numbers are allowed');
  let step = 0;
  while (n !== 1) {
    n = n % 2 === 0 ? n / 2 : 3 * n + 1;
    step++;
  }
  return step;
};