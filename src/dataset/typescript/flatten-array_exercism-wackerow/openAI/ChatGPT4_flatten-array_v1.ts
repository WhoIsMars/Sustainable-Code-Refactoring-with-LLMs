type ComplexArray = (number | undefined | ComplexArray)[];

export default class FlattenArray {
  public static flatten(_array: ComplexArray): number[] {
    const stack: (ComplexArray | number | undefined)[] = [..._array];
    const flattened: number[] = [];

    while (stack.length) {
      const item = stack.pop();
      if (typeof item === "number") {
        flattened.push(item);
      } else if (Array.isArray(item)) {
        stack.push(...item);
      }
    }

    return flattened.reverse();
  }
}