type coords = [number, number];

interface Board {
  white: coords,
  black: coords
}

export default class Queens {
  constructor(private _board: Board) {
    if (
      this.white[0] === this.black[0]
      && this.white[1] === this.black[1]
    ) {
      throw 'Queens cannot share the same space';
    }
  }

  get white(): coords {
    return this._board.white;
  }

  get black(): coords {
    return this._board.black;
  }

  public toString(): string {
    const boardArray = Array.from({ length: 8 }, (_, i) =>
      Array.from({ length: 8 }, (_, j) =>
        i === this.white[0] && j === this.white[1]
          ? 'W'
          : i === this.black[0] && j === this.black[1]
          ? 'B'
          : '_'
      ).join(' ')
    );
    return boardArray.join('\n') + '\n';
  }

  public canAttack(): boolean {
    const [wRow, wCol] = this.white;
    const [bRow, bCol] = this.black;

    return (
      wRow === bRow || // Same row
      wCol === bCol || // Same column
      Math.abs(wRow - bRow) === Math.abs(wCol - bCol) // Same diagonal
    );
  }
}