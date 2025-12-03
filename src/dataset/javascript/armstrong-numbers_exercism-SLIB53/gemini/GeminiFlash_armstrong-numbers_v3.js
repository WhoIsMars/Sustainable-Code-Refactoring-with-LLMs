const numDigits = integer => {
  return Math.floor(Math.log10(integer)) + 1;
};

const validate = integer => {
  const num_digits = numDigits(integer);
  let sum = 0;
  let temp = integer;

  for (let i = num_digits - 1; i >= 0; i--) {
    const digit = Math.floor(temp / (10 ** i));
    sum += digit ** num_digits;
    temp %= (10 ** i);
  }

  return integer === sum;
};

export { validate };