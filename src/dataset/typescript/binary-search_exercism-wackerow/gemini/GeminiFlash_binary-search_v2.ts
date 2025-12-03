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
    if (this._array.length === 0) {
      return undefined;
    }
    return this._array.slice(); // Use slice for a shallow copy
  }

  public indexOf(target: number): number {
    let low = 0;
    let high = this._array.length - 1;

    while (low <= high) {
      const mid = Math.floor((low + high) / 2);
      const midValue = this._array[mid];

      if (midValue === target) {
        return mid;
      } else if (midValue < target) {
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }

    return -1;
  }
}