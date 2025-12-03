export default class BinarySearch {
  public array: number[];

  constructor(arr: number[]) {
    if (BinarySearch.isSorted(arr)) {
      this.array = arr;
    }
  }

  private static isSorted(arr: number[]): boolean {
    for (let i = 1; i < arr.length; i++) {
      if (arr[i] < arr[i - 1]) {
        return false;
      }
    }
    return true;
  }

  private binarySearch(target: number, left: number, right: number): number {
    while (left <= right) {
      const midpoint = Math.floor((left + right) / 2);
      const value = this.array[midpoint];

      if (target === value) {
        return midpoint;
      } else if (target < value) {
        right = midpoint - 1;
      } else {
        left = midpoint + 1;
      }
    }

    return -1;
  }

  public indexOf(searchTerm: number): number {
    if (this.array === undefined) {
      throw new Error('Invalid array.');
    }
    return this.binarySearch(searchTerm, 0, this.array.length - 1);
  }
}