export default class Hamming {
  public compute(a: string, b: string): number {
    if (a.length !== b.length) { throw 'DNA strands must be of equal length.'}
    
    let counter = 0;
    const length = a.length;
    
    for (let i = 0; i < length; i++) {
      counter += +(a[i] !== b[i]);
    }
    
    return counter;
  }
}