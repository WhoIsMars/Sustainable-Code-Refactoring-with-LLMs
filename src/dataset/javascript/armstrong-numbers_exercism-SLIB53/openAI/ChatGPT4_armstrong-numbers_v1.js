const truncateHigher = (integer, order) => integer % 10 ** (order + 1);

const floorFrom = (integer, order) => integer - truncateHigher(integer, order);

const numDigits = integer => Math.floor(Math.log10(integer)) + 1;

const parseDigitAt = (integer, order) => 
  Math.floor((integer % 10 ** (order + 1)) / 10 ** order);

const parseDigits = integer => {
  const digits = [];
  let remaining = integer;
  while (remaining > 0) {
    digits.unshift(remaining % 10);
    remaining = Math.floor(remaining / 10);
  }
  return digits;
};

export const validate = integer => {
  const digits = parseDigits(integer);
  const sum = digits.reduce((acc, int) => acc + int ** digits.length, 0);
  return integer === sum;
};