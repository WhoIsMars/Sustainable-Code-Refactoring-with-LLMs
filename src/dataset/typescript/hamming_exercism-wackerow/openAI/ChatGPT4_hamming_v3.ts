export default class Hamming {
  public compute(a: string, b: string): number {
    if (a.length !== b.length) throw new Error('DNA strands must be of equal length.');
    return [...a].reduce((counter, char, i) => counter + (char !== b[i] ? 1 : 0), 0);
  }
}