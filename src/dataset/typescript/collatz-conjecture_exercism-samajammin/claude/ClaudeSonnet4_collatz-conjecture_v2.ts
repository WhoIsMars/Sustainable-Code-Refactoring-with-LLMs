class CollatzConjecture {
  static steps(int: number): number {
    if (int <= 0) {
      throw new Error('Only positive numbers are allowed');
    }
    let steps: number = 0;
    while (int !== 1) {
      if (int & 1) {
        int = int * 3 + 1;
      } else {
        int >>>= 1;
      }
      steps++;
    }
    return steps;
  }
}

export default CollatzConjecture;