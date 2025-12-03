export default class Transpose {
  static transpose(_input: string[]): string[] {
    let longestRow = 0;
    for (const row of _input) {
      longestRow = Math.max(longestRow, row.length);
    }

    const output: string[] = Array(longestRow).fill('');
    for (let i = 0; i < _input.length; i++) {
      const row = _input[i];
      for (let j = 0; j < longestRow; j++) {
        if (row[j]) {
          output[j] = output[j] || '';
          output[j] += row[j];
        } else {
          output[j] = output[j] || '';
          if (output[j].trim() === '') {
            output[j] += ' ';
          }
        }
      }
    }
    return output;
  }
}