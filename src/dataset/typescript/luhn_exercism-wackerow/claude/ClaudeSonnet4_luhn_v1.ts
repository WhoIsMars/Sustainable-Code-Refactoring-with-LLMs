export default class Luhn {
  public static valid(_numbers: string): boolean {
    // Sanitize and remove all spaces
    const numbers = _numbers.replace(/\s/g, '');
    
    // If too short, or contains anything other than numbers, return false
    if (numbers.length < 2 || /[^0-9]/.test(numbers)) {
      return false;
    }
    
    let sum = 0;
    const length = numbers.length;
    
    // Process digits from right to left, excluding checksum digit
    for (let i = length - 2; i >= 0; i--) {
      let digit = +numbers[i];
      
      // Double every second digit from right (excluding checksum)
      if ((length - i) % 2 === 0) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      
      sum += digit;
    }
    
    const checksum = +numbers[length - 1];
    return (sum * 9) % 10 === checksum;
  }
}