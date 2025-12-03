export default class ArmstrongNumbers {
  static isArmstrongNumber(num: number): boolean {
    const str = num.toString();
    const length = str.length;
    let sum = 0;
    
    for (let i = 0; i < length; i++) {
      const digit = str.charCodeAt(i) - 48; // Convert char to number directly
      sum += digit ** length;
    }

    return sum === num;
  }
}