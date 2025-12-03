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
    
    while (int !== 1 && !this.cache.has(int)) {
      int = (int & 1) === 0 ? int >>> 1 : int * 3 + 1;
      steps++;
    }
    
    if (int !== 1) {
      steps += this.cache.get(int)!;
    }
    
    this.cache.set(original, steps);
    return steps;
  }
}

export default CollatzConjecture;