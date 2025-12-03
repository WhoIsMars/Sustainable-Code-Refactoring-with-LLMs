const truncateHigher = (integer, order) => {
  const pow10 = Math.pow(10, order + 1);
  return integer % pow10;
};

const floorFrom = (integer, order) => {
  const pow10 = Math.pow(10, order + 1);
  return integer - (integer % pow10);
};

const numDigits = integer => {
  if (integer === 0) return 1;
  return Math.floor(Math.log10(integer)) + 1;
};

const parseDigitAt = (integer, order) => {
  const pow10 = Math.pow(10, order);
  const digit = Math.floor(integer / pow10) % 10;
  return digit;
};

const parseDigits = integer => {
  const num_dig = numDigits(integer);
  const buf = new Array(num_dig);
  for (let z = num_dig - 1; z >= 0; z -= 1) {
    buf[num_dig - 1 - z] = parseDigitAt(integer, z);
  }
  return buf;
};

export const validate = integer => {
  const digits = parseDigits(integer);
  let sum = 0;
  const len = digits.length;
  for (let i = 0; i < len; i++) {
    sum += Math.pow(digits[i], len);
  }
  return integer === sum;
};