class CollatzConjecture {
  static steps(int: number): number {
    if (int <= 0) {
      throw new Error('Only positive numbers are allowed');
    }

    let steps = 0;
    let n = int;

    while (n !== 1) {
      if ((n & 1) === 0) {
        n >>>= 1;
      } else {
        n = 3 * n + 1;
      }
      steps++;
    }

    return steps;
  }
}

export default CollatzConjecture;