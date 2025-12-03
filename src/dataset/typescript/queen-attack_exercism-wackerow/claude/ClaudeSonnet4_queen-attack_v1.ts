type coords = [number, number];

interface Board {
  white: coords,
  black: coords
}

export default class Queens {
  private _white: coords;
  private _black: coords;

  constructor(private _board: Board) {
    this._white = _board.white;
    this._black = _board.black;
    
    if (this._white[0] === this._black[0] && this._white[1] === this._black[1]) {
      throw 'Queens cannot share the same space';
    }
  }

  get white(): coords {
    return [...this._white];
  }

  get black(): coords {
    return [...this._black];
  }

  public toString(): string {
    const whiteRow = this._white[0];
    const whiteCol = this._white[1];
    const blackRow = this._black[0];
    const blackCol = this._black[1];
    
    let result = '';
    for (let i = 0; i < 8; i++) {
      for (let j = 0; j < 8; j++) {
        if (i === whiteRow && j === whiteCol) {
          result += 'W';
        } else if (i === blackRow && j === blackCol) {
          result += 'B';
        } else {
          result += '_';
        }
        if (j < 7) result += ' ';
      }
      result += '\n';
    }
    return result;
  }

  public canAttack(): boolean {
    const [whiteRow, whiteCol] = this._white;
    const [blackRow, blackCol] = this._black;
    
    // Check same row or column
    if (whiteRow === blackRow || whiteCol === blackCol) {
      return true;
    }
    
    // Check diagonals
    const rowDiff = Math.abs(whiteRow - blackRow);
    const colDiff = Math.abs(whiteCol - blackCol);
    
    return rowDiff === colDiff;
  }
}