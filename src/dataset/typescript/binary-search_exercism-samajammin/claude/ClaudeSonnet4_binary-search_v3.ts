export default class BinarySearch {
  public array: number[]

  constructor(arr: number[]) {
    if (this.isSorted(arr)) {
      this.array = arr
    }
  }

  private isSorted(arr: number[]): boolean {
    for (let i = 1; i < arr.length; i++) {
      if (arr[i] < arr[i - 1]) {
        return false
      }
    }
    return true
  }

  private binarySearch(target: number, left: number, right: number): number {
    while (left <= right) {
      const midpoint = left + Math.floor((right - left) / 2)
      const value = this.array[midpoint]
      
      if (target === value) {
        return midpoint
      } else if (target > value) {
        left = midpoint + 1
      } else {
        right = midpoint - 1
      }
    }
    return -1
  }

  public indexOf(searchTerm: number): number {
    if (this.array === undefined) {
      throw new Error('Invalid array.')
    }
    return this.binarySearch(searchTerm, 0, this.array.length - 1)
  }
}