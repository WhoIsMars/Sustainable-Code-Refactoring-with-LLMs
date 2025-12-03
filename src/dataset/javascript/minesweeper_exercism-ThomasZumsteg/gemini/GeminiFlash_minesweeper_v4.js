class Minesweeper {
    static countMines(field, row, col) {
        let total = 0;
        const numRows = field.length;
        const numCols = field[0].length;

        for (let i = Math.max(0, row - 1); i <= Math.min(numRows - 1, row + 1); i++) {
            for (let j = Math.max(0, col - 1); j <= Math.min(numCols - 1, col + 1); j++) {
                if (i === row && j === col) continue;
                if (field[i][j] === '*') {
                    total++;
                }
            }
        }
        return total;
    }

    annotate(field) {
        const numRows = field.length;
        if (numRows === 0) return [];
        const numCols = field[0].length;

        const annotatedField = field.map(row => row.split(''));

        for (let r = 0; r < numRows; r++) {
            for (let c = 0; c < numCols; c++) {
                if (annotatedField[r][c] === ' ') {
                    const mines = Minesweeper.countMines(annotatedField, r, c);
                    annotatedField[r][c] = mines === 0 ? ' ' : String(mines);
                }
            }
        }

        return annotatedField.map(row => row.join(''));
    }
}

module.exports = Minesweeper