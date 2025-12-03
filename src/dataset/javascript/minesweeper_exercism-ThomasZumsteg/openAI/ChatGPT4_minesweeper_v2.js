class Minesweeper {
    static countMines(field, row, col) {
        let total = 0;
        for (let dr = -1; dr <= 1; dr++) {
            for (let dc = -1; dc <= 1; dc++) {
                if (dr === 0 && dc === 0) continue;
                const newRow = row + dr, newCol = col + dc;
                if (newRow >= 0 && newRow < field.length &&
                    newCol >= 0 && newCol < field[newRow].length &&
                    field[newRow][newCol] === '*') {
                    total++;
                }
            }
        }
        return total;
    }

    annotate(field) {
        const result = field.map((row, r) => 
            row.split('').map((cell, c) => {
                if (cell === ' ') {
                    const mines = Minesweeper.countMines(field.map(row => row.split('')), r, c);
                    return mines === 0 ? ' ' : mines;
                }
                return cell;
            }).join('')
        );
        return result;
    }
}

module.exports = Minesweeper;