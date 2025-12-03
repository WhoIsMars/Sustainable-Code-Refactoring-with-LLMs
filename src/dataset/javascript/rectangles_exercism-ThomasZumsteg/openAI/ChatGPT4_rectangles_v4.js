function is_rectangle(diagram, top_left, bottom_right) {
    if (
        diagram[top_left.row][top_left.col] !== '+' ||
        diagram[bottom_right.row][bottom_right.col] !== '+' ||
        diagram[bottom_right.row][top_left.col] !== '+' ||
        diagram[top_left.row][bottom_right.col] !== '+'
    ) return false;

    for (let row = top_left.row + 1; row < bottom_right.row; row++) {
        if (diagram[row][top_left.col] !== '|' && diagram[row][top_left.col] !== '+') return false;
        if (diagram[row][bottom_right.col] !== '|' && diagram[row][bottom_right.col] !== '+') return false;
    }

    for (let col = top_left.col + 1; col < bottom_right.col; col++) {
        if (diagram[top_left.row][col] !== '-' && diagram[top_left.row][col] !== '+') return false;
        if (diagram[bottom_right.row][col] !== '-' && diagram[bottom_right.row][col] !== '+') return false;
    }

    return true;
}

module.exports = function (diagram) {
    const rows = diagram.length;
    const cols = diagram[0].length;
    let count = 0;

    const plusPositions = [];
    for (let r = 0; r < rows; r++) {
        for (let c = 0; c < cols; c++) {
            if (diagram[r][c] === '+') {
                plusPositions.push({ row: r, col: c });
            }
        }
    }

    for (let i = 0; i < plusPositions.length; i++) {
        const top_left = plusPositions[i];
        for (let j = i + 1; j < plusPositions.length; j++) {
            const bottom_right = plusPositions[j];
            if (
                top_left.row < bottom_right.row &&
                top_left.col < bottom_right.col &&
                is_rectangle(diagram, top_left, bottom_right)
            ) {
                count++;
            }
        }
    }

    return count;
};