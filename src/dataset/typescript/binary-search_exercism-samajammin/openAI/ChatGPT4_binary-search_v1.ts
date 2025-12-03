export default class BinarySearch {
  public array: number[];

  constructor(arr: number[]) {
    if (arr.every((val, i, a) => i === 0 || a[i - 1] <= val)) {
      this.array = arr;
    } else {
      throw new Error('Array must be sorted.');
    }
  }

  private binarySearch(target: number, left: number, right: number): number {
    while (left <= right) {
      const midpoint = Math.floor((left + right) / 2);
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