export default class Transpose {
  static transpose(_input: string[]): string[] {
    if (_input.length === 0) return [];
    
    let longestRow = 0;
    for (let i = 0; i < _input.length; i++) {
      if (_input[i].length > longestRow) {
        longestRow = _input[i].length;
      }
    }
    
    const output: string[] = new Array(longestRow);
    
    for (let i = 0; i < longestRow; i++) {
      let newRow = '';
      let hasNonSpace = false;
      
      for (let j = 0; j < _input.length; j++) {
        const char = _input[j][i];
        if (char !== undefined) {
          newRow += char;
          if (char !== ' ') hasNonSpace = true;
        } else {
          newRow += hasNonSpace ? ' ' : '';
        }
      }
      
      output[i] = newRow;
    }
    
    return output;
  }
}