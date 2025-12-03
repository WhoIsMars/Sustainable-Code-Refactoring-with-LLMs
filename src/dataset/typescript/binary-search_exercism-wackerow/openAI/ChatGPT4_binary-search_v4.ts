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
    return this._array.length > 0 ? this._array : undefined;
  }

  public indexOf(target: number, iStart: number = 0, iEnd: number = this._array.length - 1): number {
    while (iStart <= iEnd) {
      const mid = Math.floor((iStart + iEnd) / 2);
      if (this._array[mid] === target) return mid;
      if (this._array[mid] < target) {
        iStart = mid + 1;
      } else {
        iEnd = mid - 1;
      }
    }
    return -1;
  }
}