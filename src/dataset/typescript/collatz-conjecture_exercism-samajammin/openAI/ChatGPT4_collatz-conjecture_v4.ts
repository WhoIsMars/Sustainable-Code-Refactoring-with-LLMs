class CollatzConjecture {
  static steps(int: number): number {
    if (int <= 0) throw new Error('Only positive numbers are allowed');
    let steps = 0;
    while (int !== 1) {
      steps++;
      int = (int & 1) === 0 ? int >> 1 : int * 3 + 1;
    }
    return steps;
  }
}

export default CollatzConjecture;