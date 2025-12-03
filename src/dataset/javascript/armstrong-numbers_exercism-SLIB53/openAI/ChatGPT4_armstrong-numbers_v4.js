const truncateHigher = (integer, order) => integer % 10 ** (order + 1);

const floorFrom = (integer, order) => integer - truncateHigher(integer, order);

const numDigits = integer => Math.floor(Math.log10(integer)) + 1;

const parseDigits = integer => {
  const digits = [];
  while (integer > 0) {
    digits.unshift(integer % 10);
    integer = Math.floor(integer / 10);
  }
  return digits;
};

export const validate = integer => {
  const digits = parseDigits(integer);
  const sum = digits.reduce((acc, digit) => acc + digit ** digits.length, 0);
  return integer === sum;
};