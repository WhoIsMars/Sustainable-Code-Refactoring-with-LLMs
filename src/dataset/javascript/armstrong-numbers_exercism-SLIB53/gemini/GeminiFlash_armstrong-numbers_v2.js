const numDigits = integer => {
  return Math.floor(Math.log10(integer)) + 1;
};

const parseDigits = integer => {
  const num_dig = numDigits(integer);
  const digits = new Array(num_dig);
  let remaining = integer;

  for (let i = num_dig - 1; i >= 0; i--) {
    const powerOfTen = 10 ** i;
    digits[i] = Math.floor(remaining / powerOfTen);
    remaining %= powerOfTen;
  }

  return digits;
};

export const validate = integer => {
  const digits = parseDigits(integer);
  let sum = 0;
  const numDigits = digits.length;

  for (let i = 0; i < numDigits; i++) {
    sum += digits[i] ** numDigits;
  }

  return integer === sum;
};