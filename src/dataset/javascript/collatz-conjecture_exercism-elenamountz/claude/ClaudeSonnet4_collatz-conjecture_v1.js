export const steps = (n) => {
  if(n <= 0){
    throw new Error('Only positive numbers are allowed');
  }
  
  let number = n;
  let step = 0;
  
  while(number !== 1) {
    if(number % 2 === 0) {
      number = number / 2;
    } else {
      number = (3 * number) + 1;
    }
    step++;
  }
  
  return step;
};