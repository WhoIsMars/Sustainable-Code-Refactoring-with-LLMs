class CollatzConjecture {
  private static cache = new Map<number, number>();

  static steps(int: number): number {
    if (int <= 0) {
      throw new Error('Only positive numbers are allowed');
    }

    if (this.cache.has(int)) {
      return this.cache.get(int)!;
    }

    const original = int;
    let steps = 0;
    const path: number[] = [];

    while (int !== 1 && !this.cache.has(int)) {
      path.push(int);
      int = (int & 1) === 0 ? int >>> 1 : int * 3 + 1;
      steps++;
    }

    const baseSteps = int === 1 ? 0 : this.cache.get(int)!;
    
    for (let i = path.length - 1; i >= 0; i--) {
      this.cache.set(path[i], baseSteps + steps - i);
    }

    return this.cache.get(original)!;
  }
}

export default CollatzConjecture;