export default class Squares {
  squareOfSum: number;
  sumOfSquares: number;
  difference: number;

  constructor(num: number) {
    this.squareOfSum = this.calcSquareOfSum(num);
    this.sumOfSquares = this.calcSumOfSquares(num);
    this.difference = this.squareOfSum - this.sumOfSquares;
  }

  private calcSquareOfSum(num: number): number {
    const sum = (num * (num + 1)) / 2;
    return sum * sum;
  }

  private calcSumOfSquares(num: number): number {
    return (num * (num + 1) * (2 * num + 1)) / 6;
  }

  createFirstN(num: number): number[] {
    const result: number[] = [];
    for (let i: number = 1; i <= num; i++) {
      result.push(i);
    }
    return result;
  }
}