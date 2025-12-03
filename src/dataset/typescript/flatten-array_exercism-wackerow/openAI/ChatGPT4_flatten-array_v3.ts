type ComplexArray = (number | undefined | ComplexArray)[];

export default class FlattenArray {
  public static flatten(_array: ComplexArray): number[] {
    return _array.reduce<number[]>((flattened, item) => {
      if (typeof item === "number") {
        flattened.push(item);
      } else if (Array.isArray(item)) {
        flattened.push(...this.flatten(item));
      }
      return flattened;
    }, []);
  }
}