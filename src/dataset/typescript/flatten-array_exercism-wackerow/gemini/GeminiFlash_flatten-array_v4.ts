type ComplexArray = (number | undefined | ComplexArray)[];

export default class FlattenArray {
  public static flatten(_array: ComplexArray): number[] {
    const flattened: number[] = [];
    const stack: ComplexArray = [_array];

    while (stack.length > 0) {
      const current = stack.pop();
      if (current && Array.isArray(current)) {
        for (let i = current.length - 1; i >= 0; i--) {
          const item = current[i];
          if (typeof item === 'number') {
            flattened.push(item);
          } else if (Array.isArray(item)) {
            stack.push(item);
          }
        }
      }
    }

    return flattened.reverse();
  }
}