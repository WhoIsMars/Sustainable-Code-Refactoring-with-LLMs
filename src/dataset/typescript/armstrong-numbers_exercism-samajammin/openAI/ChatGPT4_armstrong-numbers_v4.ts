export default class ArmstrongNumbers {
  static isArmstrongNumber(num: number): boolean {
    const numStr = num.toString();
    const len = numStr.length;
    let sum = 0;

    for (let i = 0; i < len; i++) {
      const digit = Number(numStr[i]);
      sum += Math.pow(digit, len);
      if (sum > num) return false;
    }

    return sum === num;
  }
}