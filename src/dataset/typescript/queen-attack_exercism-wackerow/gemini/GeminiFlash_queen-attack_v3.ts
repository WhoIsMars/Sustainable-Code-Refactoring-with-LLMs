type coords = [number, number];

interface Board {
  white: coords;
  black: coords;
}

export default class Queens {
  private readonly _white: coords;
  private readonly _black: coords;

  constructor(board: Board) {
    if (board.white[0] === board.black[0] && board.white[1] === board.black[1]) {
      throw 'Queens cannot share the same space';
    }
    this._white = board.white;
    this._black = board.black;
  }

  get white(): coords {
    return this._white;
  }

  get black(): coords {
    return this._black;
  }

  public toString(): string {
    let boardString = '';
    for (let i = 0; i < 8; i++) {
      for (let j = 0; j < 8; j++) {
        if (i === this._white[0] && j === this._white[1]) {
          boardString += 'W';
        } else if (i === this._black[0] && j === this._black[1]) {
          boardString += 'B';
        } else {
          boardString += '_';
        }
        if (j < 7) {
          boardString += ' ';
        }
      }
      boardString += '\n';
    }
    return boardString;
  }

  public canAttack(): boolean {
    const [whiteRow, whiteCol] = this._white;
    const [blackRow, blackCol] = this._black;

    if (whiteRow === blackRow || whiteCol === blackCol) {
      return true;
    }

    if (Math.abs(whiteRow - blackRow) === Math.abs(whiteCol - blackCol)) {
      return true;
    }

    return false;
  }
}