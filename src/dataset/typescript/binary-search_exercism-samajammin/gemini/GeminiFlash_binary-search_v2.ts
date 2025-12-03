export default class BinarySearch {
  public array: number[];

  constructor(arr: number[]) {
    if (BinarySearch.isSorted(arr)) {
      this.array = arr;
    } else {
      this.array = [];
    }
  }

  private static isSorted(arr: number[]): boolean {
    if (arr.length <= 1) {
      return true;
    }
    for (let i = 1; i < arr.length; i++) {
      if (arr[i] < arr[i - 1]) {
        return false;
      }
    }
    return true;
  }

  public indexOf(searchTerm: number): number {
    if (!this.array || this.array.length === 0) {
      throw new Error('Invalid array.');
    }

    let left = 0;
    let right = this.array.length - 1;

    while (left <= right) {
      const midpoint = Math.floor((left + right) / 2);
      const value = this.array[midpoint];

      if (searchTerm === value) {
        return midpoint;
      } else if (searchTerm < value) {
        right = midpoint - 1;
      } else {
        left = midpoint + 1;
      }
    }

    return -1;
  }
}