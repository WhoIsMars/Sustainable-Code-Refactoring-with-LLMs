export default class Transpose {
  static transpose(_input: string[]): string[] {
    if (!_input.length) {
      return [];
    }

    let longestRow = 0;
    for (const row of _input) {
      longestRow = Math.max(longestRow, row.length);
    }

    const output: string[] = Array(longestRow).fill('');

    for (const row of _input) {
      for (let j = 0; j < longestRow; j++) {
        if (j < row.length) {
          output[j] += row[j];
        } else {
          output[j] += ' ';
        }
      }
    }

    return output;
  }
}