export default class BinarySearch {
  private _array: number[] = [];

  constructor(array: number[]) {
    let isSorted = true;
    for (let i = 1; i < array.length && isSorted; i++) {
      if (array[i] < array[i-1]) {
        isSorted = false;
      }
    }
    if (isSorted) {
      this._array = array;
    }
  }

  get array() {
    return this._array.length === 0 ? undefined : [...this._array];
  }

  public indexOf(target: number, iStart: number = 0, iEnd: number = this._array.length): number {
    let start = iStart;
    let end = iEnd;
    
    while (start < end) {
      const mid = Math.floor((start + end) / 2);
      const midValue = this._array[mid];
      
      if (midValue === target) {
        return mid;
      }
      
      if (target > midValue) {
        start = mid + 1;
      } else {
        end = mid;
      }
    }
    
    return -1;
  }
}