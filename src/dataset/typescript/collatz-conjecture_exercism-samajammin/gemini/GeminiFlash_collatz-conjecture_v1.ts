class CollatzConjecture {
  static steps(int: number): number {
    if (int <= 0) {
      throw new Error('Only positive numbers are allowed');
    }

    let steps = 0;
    while (int !== 1) {
      if ((int & 1) === 0) {
        int /= 2;
      } else {
        int = 3 * int + 1;
      }
      steps++;
    }
    return steps;
  }
}

export default CollatzConjecture;