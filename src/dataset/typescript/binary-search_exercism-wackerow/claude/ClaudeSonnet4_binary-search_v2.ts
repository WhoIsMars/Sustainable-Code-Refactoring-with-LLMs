export default class BinarySearch {
  private _array: number[] = [];

  constructor(array: number[]) {
    for (let i = 1; i < array.length; i++) {
      if (array[i] < array[i-1]) {
        return;
      }
    }
    this._array = array;
  }

  get array() {
    if (this._array.length === 0) { return undefined;}
    return [...this._array];
  }

  public indexOf(target: number, iStart: number = 0, iEnd: number = this._array.length): number {
    // Iterative approach to avoid call stack overhead
    let start = iStart;
    let end = iEnd;
    
    while (start < end) {
      const mid = start + ((end - start) >>> 1); // Bit shift for faster division
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