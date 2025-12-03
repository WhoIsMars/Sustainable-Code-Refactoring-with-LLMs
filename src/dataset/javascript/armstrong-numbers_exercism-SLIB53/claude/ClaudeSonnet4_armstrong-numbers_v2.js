export const validate = integer => {
  const str = integer.toString();
  const length = str.length;
  let sum = 0;
  
  for (let i = 0; i < length; i++) {
    const digit = str.charCodeAt(i) - 48; // Convert char to digit
    sum += digit ** length;
  }
  
  return integer === sum;
};