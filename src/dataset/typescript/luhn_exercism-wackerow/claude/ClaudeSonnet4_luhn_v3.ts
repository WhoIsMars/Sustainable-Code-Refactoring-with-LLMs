export default class Luhn {
  public static valid(_numbers: string): boolean {
    const numbers = _numbers.replace(/\s/g, '');
    
    if (numbers.length < 2 || !/^\d+$/.test(numbers)) {
      return false;
    }
    
    let sum = 0;
    let isEven = numbers.length % 2 === 0;
    
    for (let i = 0; i < numbers.length - 1; i++) {
      let digit = +numbers[i];
      
      if (isEven) {
        digit *= 2;
        if (digit > 9) {
          digit -= 9;
        }
      }
      
      sum += digit;
      isEven = !isEven;
    }
    
    const checksum = +numbers[numbers.length - 1];
    return (sum * 9) % 10 === checksum;
  }
}