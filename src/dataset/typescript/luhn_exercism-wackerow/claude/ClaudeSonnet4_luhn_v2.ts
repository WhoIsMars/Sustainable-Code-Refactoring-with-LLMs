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
    
    // Process all digits except the last one (checksum)
    for (let i = 0; i < length - 1; i++) {
      let digit = +numbers[i];
      
      // Every other position from the right gets doubled
      if ((i + length) % 2 === 0) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      
      sum += digit;
    }
    
    // Check if (sum * 9) % 10 equals the checksum digit
    return (sum * 9) % 10 === +numbers[length - 1];
  }
}