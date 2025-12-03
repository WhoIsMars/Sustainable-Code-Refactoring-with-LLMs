const BOARD_SIZE = 8;
type Coordinates = [number, number];

export default class QueenAttack {
  white: Coordinates;
  black: Coordinates;

  constructor({ white, black }: { white: Coordinates; black: Coordinates }) {
    if (white[0] === black[0] && white[1] === black[1]) {
      throw new Error('Queens cannot share the same space');
    }
    this.white = white;
    this.black = black;
  }

  toString() {
    const result: string[] = [];
    
    for (let row = 0; row < BOARD_SIZE; row++) {
      const rowChars: string[] = [];
      for (let col = 0; col < BOARD_SIZE; col++) {
        if (row === this.white[0] && col === this.white[1]) {
          rowChars.push('W');
        } else if (row === this.black[0] && col === this.black[1]) {
          rowChars.push('B');
        } else {
          rowChars.push('_');
        }
      }
      result.push(rowChars.join(' '));
    }
    
    return result.join('\n') + '\n';
  }

  canAttack() {
    const rowDiff = Math.abs(this.white[0] - this.black[0]);
    const colDiff = Math.abs(this.white[1] - this.black[1]);

    return rowDiff === 0 || colDiff === 0 || rowDiff === colDiff;
  }
}