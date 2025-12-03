function is_rectangle(diagram, top_left, bottom_right) {
    const tlRow = top_left.row;
    const tlCol = top_left.col;
    const brRow = bottom_right.row;
    const brCol = bottom_right.col;

    if (diagram[tlRow][tlCol] !== '+' ||
        diagram[brRow][brCol] !== '+' ||
        diagram[brRow][tlCol] !== '+' ||
        diagram[tlRow][brCol] !== '+') {
        return false;
    }

    for (let row = tlRow + 1; row < brRow; row++) {
        const left = diagram[row][tlCol];
        const right = diagram[row][brCol];
        if ((left !== '|' && left !== '+') || (right !== '|' && right !== '+')) {
            return false;
        }
    }

    for (let col = tlCol + 1; col < brCol; col++) {
        const top = diagram[tlRow][col];
        const bottom = diagram[brRow][col];
        if ((top !== '-' && top !== '+') || (bottom !== '-' && bottom !== '+')) {
            return false;
        }
    }

    return true;
}

module.exports = function(diagram) {
    let count = 0;
    const rows = diagram.length;

    for (let r = 0; r < rows - 1; r++) {
        const cols = diagram[r].length;
        for (let c = 0; c < cols - 1; c++) {
            if (diagram[r][c] === '+') {
                for (let i = r + 1; i < rows; i++) {
                    const innerCols = diagram[i].length;
                    for (let j = c + 1; j < innerCols; j++) {
                        if (diagram[i][j] === '+' && diagram[r][j] === '+' && diagram[i][c] === '+' && is_rectangle(diagram, { row: r, col: c }, { row: i, col: j })) {
                            count++;
                        }
                    }
                }
            }
        }
    }
    return count;
};