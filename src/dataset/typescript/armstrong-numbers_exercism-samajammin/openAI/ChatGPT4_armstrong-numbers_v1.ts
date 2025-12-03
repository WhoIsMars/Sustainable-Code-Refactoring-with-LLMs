export default class ArmstrongNumbers {
  static isArmstrongNumber(num: number): boolean {
    const digits = num.toString();
    const length = digits.length;
    let sum = 0;

    for (let i = 0; i < length; i++) {
      const digit = Number(digits[i]);
      sum += digit ** length;
      if (sum > num) return false; // Early exit if sum exceeds num
    }

    return sum === num;
  }
}