export default class Transpose {
  static transpose(_input: string[]): string[] {
    const longestRow: number = _input.reduce(
      (state, row) => Math.max(state, row.length), 0
    );

    const output: string[] = Array(longestRow).fill('');

    for (let i = 0; i < _input.length; i++) {
      const row = _input[i];
      for (let j = 0; j < longestRow; j++) {
        const char = row[j] || ' ';
        output[j] = (output[j] || '').padEnd(i, ' ') + char;
      }
    }

    return output;
  }
}