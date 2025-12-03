export default class BinarySearch {
  private _array: number[];

  constructor(array: number[]) {
    if (array.every((val, i, arr) => i === 0 || arr[i - 1] <= val)) {
      this._array = array;
    } else {
      this._array = [];
    }
  }

  get array(): number[] | undefined {
    return this._array.length ? this._array : undefined;
  }

  public indexOf(target: number, iStart: number = 0, iEnd: number = this._array.length - 1): number {
    while (iStart <= iEnd) {
      const indexToCheck = Math.floor((iStart + iEnd) / 2);
      if (this._array[indexToCheck] === target) return indexToCheck;
      if (target > this._array[indexToCheck]) {
        iStart = indexToCheck + 1;
      } else {
        iEnd = indexToCheck - 1;
      }
    }
    return -1;
  }
}