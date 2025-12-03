type ComplexArray = (number | undefined | ComplexArray)[];

export default class FlattenArray {
  public static flatten(_array: ComplexArray): number[] {
    const flattened: number[] = [];
    this.flattenHelper(_array, flattened);
    return flattened;
  }

  private static flattenHelper(_array: ComplexArray, flattened: number[]): void {
    for (let i = 0; i < _array.length; i++) {
      const item = _array[i];
      if (typeof item === "number") {
        flattened.push(item);
      } else if (Array.isArray(item)) {
        this.flattenHelper(item, flattened);
      }
    }
  }
}