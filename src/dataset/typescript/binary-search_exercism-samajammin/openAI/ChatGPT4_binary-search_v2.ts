export default class BinarySearch {
  private array: number[];

  constructor(arr: number[]) {
    if (this.isSorted(arr)) {
      this.array = arr;
    } else {
      throw new Error('Array must be sorted.');
    }
  }

  private isSorted(arr: number[]): boolean {
    return arr.every((val, i, a) => i === 0 || a[i - 1] <= val);
  }

  private binarySearch(target: number, left: number, right: number): number {
    while (left <= right) {
      const midpoint = left + Math.floor((right - left) / 2);
      const value = this.array[midpoint];

      if (value === target) {
        return midpoint;
      } else if (value < target) {
        left = midpoint + 1;
      } else {
        right = midpoint - 1;
      }
    }
    return -1;
  }

  public indexOf(searchTerm: number): number {
    if (!this.array) {
      throw new Error('Invalid array.');
    }
    return this.binarySearch(searchTerm, 0, this.array.length - 1);
  }
}