export default class BinarySearch {
  private _array: number[];

  constructor(array: number[]) {
    if (!this.isSorted(array)) {
      this._array = [];
      return;
    }
    this._array = array;
  }

  private isSorted(array: number[]): boolean {
    for (let i = 1; i < array.length; i++) {
      if (array[i] < array[i - 1]) {
        return false;
      }
    }
    return true;
  }

  get array() {
    return this._array.length === 0 ? undefined : [...this._array];
  }

  public indexOf(target: number, iStart: number = 0, iEnd: number = this._array.length): number {
    let start = iStart;
    let end = iEnd;

    while (start < end) {
      const indexToCheck = Math.floor((start + end) / 2);

      if (this._array[indexToCheck] === target) {
        return indexToCheck;
      }

      if (target > this._array[indexToCheck]) {
        start = indexToCheck + 1;
      } else {
        end = indexToCheck;
      }
    }

    return -1;
  }
}