type coords = [number, number];

interface Board {
  white: coords;
  black: coords;
}

export default class Queens {
  private readonly whiteRow: number;
  private readonly whiteCol: number;
  private readonly blackRow: number;
  private readonly blackCol: number;

  constructor(private _board: Board) {
    this.whiteRow = _board.white[0];
    this.whiteCol = _board.white[1];
    this.blackRow = _board.black[0];
    this.blackCol = _board.black[1];

    if (this.whiteRow === this.blackRow && this.whiteCol === this.blackCol) {
      throw 'Queens cannot share the same space';
    }
  }

  get white(): coords {
    return [this.whiteRow, this.whiteCol];
  }

  get black(): coords {
    return [this.blackRow, this.blackCol];
  }

  public toString(): string {
    let boardString = '';
    for (let i = 0; i < 8; i++) {
      for (let j = 0; j < 8; j++) {
        if (i === this.whiteRow && j === this.whiteCol) {
          boardString += 'W';
        } else if (i === this.blackRow && j === this.blackCol) {
          boardString += 'B';
        } else {
          boardString += '_';
        }
        boardString += ' ';
      }
      boardString = boardString.slice(0, -1) + '\n';
    }
    return boardString;
  }

  public canAttack(): boolean {
    if (this.whiteRow === this.blackRow) return true;
    if (this.whiteCol === this.blackCol) return true;
    if (Math.abs(this.whiteRow - this.blackRow) === Math.abs(this.whiteCol - this.blackCol)) return true;
    return false;
  }
}