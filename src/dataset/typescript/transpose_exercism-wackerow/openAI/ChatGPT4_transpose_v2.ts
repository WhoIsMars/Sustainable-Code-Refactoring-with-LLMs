export default class Transpose {
  static transpose(_input: string[]): string[] {
    const longestRow = Math.max(..._input.map(row => row.length));
    const output: string[] = Array.from({ length: longestRow }, (_, i) => 
      _input.map(row => row[i] || ' ').join('').replace(/\s+$/, '')
    );
    return output;
  }
}