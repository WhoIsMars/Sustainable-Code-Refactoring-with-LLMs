const truncateHigher = (integer, order) => {
  return integer % (10 ** (order + 1));
};

const floorFrom = (integer, order) => {
  return integer - truncateHigher(integer, order);
};

const numDigits = integer => {
  return integer === 0 ? 1 : Math.floor(Math.log10(Math.abs(integer))) + 1;
};

const parseDigitAt = (integer, order) => {
  return Math.floor(integer / (10 ** order)) % 10;
};

const parseDigits = integer => {
  const digits = numDigits(integer);
  const buf = new Array(digits);
  let temp = Math.abs(integer);
  
  for (let i = digits - 1; i >= 0; i--) {
    buf[i] = temp % 10;
    temp = Math.floor(temp / 10);
  }
  
  return buf;
};

export const validate = integer => {
  if (integer <= 0) return false;
  
  const digits = parseDigits(integer);
  const power = digits.length;
  let sum = 0;
  
  for (let i = 0; i < digits.length; i++) {
    sum += digits[i] ** power;
  }
  
  return integer === sum;
};