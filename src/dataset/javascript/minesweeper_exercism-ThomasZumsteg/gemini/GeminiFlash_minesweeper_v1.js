class Minesweeper {
    static countMines(field, row, col) {
        let total = 0;
        for (let i = Math.max(0, row - 1); i <= Math.min(field.length - 1, row + 1); i++) {
            for (let j = Math.max(0, col - 1); j <= Math.min(field[0].length - 1, col + 1); j++) {
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

        const result = field.map(row => row.split(''));

        for (let r = 0; r < numRows; r++) {
            for (let c = 0; c < numCols; c++) {
                if (result[r][c] === ' ') {
                    const mines = Minesweeper.countMines(result, r, c);
                    if (mines > 0) {
                        result[r][c] = mines.toString();
                    }
                }
            }
        }

        return result.map(row => row.join(''));
    }
}

module.exports = Minesweeper