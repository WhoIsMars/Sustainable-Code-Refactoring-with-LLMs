const truncateHigher = (integer, order) => {
  return integer % (10 ** (order + 1));
};

const floorFrom = (integer, order) => {
  return integer - truncateHigher(integer, order);
};

const numDigits = integer => {
  return integer === 0 ? 1 : Math.floor(Math.log10(integer)) + 1;
};

const parseDigitAt = (integer, order) => {
  return Math.floor(integer / (10 ** order)) % 10;
};

const parseDigits = integer => {
  if (integer === 0) return [0];
  
  const digits = [];
  let temp = integer;
  
  while (temp > 0) {
    digits.unshift(temp % 10);
    temp = Math.floor(temp / 10);
  }
  
  return digits;
};

export const validate = integer => {
  if (integer === 0) return false;
  
  const digits = parseDigits(integer);
  const power = digits.length;
  
  let sum = 0;
  for (let i = 0; i < digits.length; i++) {
    sum += digits[i] ** power;
  }
  
  return integer === sum;
};