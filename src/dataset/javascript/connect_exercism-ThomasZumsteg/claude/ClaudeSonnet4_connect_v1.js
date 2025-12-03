function transpose(board) {
    const rows = board.length;
    const cols = board[0].length;
    const result = new Array(cols);
    for (let i = 0; i < cols; i++) {
        result[i] = new Array(rows);
        for (let j = 0; j < rows; j++) {
            result[i][j] = board[j][i];
        }
    }
    return result;
}

function hash(element) {
    return element.row + ':' + element.col;
}

function has_path(board, letter) {
    const seen = new Set();
    const queue = [];
    const firstRow = board[0];
    
    for (let i = 0; i < firstRow.length; i++) {
        if (firstRow[i] === letter) {
            queue.push({row: 0, col: i});
        }
    }
    
    const directions = [
        {dr: -1, dc: 0}, {dr: -1, dc: 1}, 
        {dr: 0, dc: 1}, {dr: 0, dc: -1},
        {dr: 1, dc: -1}, {dr: 1, dc: 0}
    ];
    
    const boardHeight = board.length;
    
    while (queue.length > 0) {
        const elem = queue.pop();
        const key = hash(elem);
        
        if (seen.has(key) || elem.row < 0 || elem.row >= boardHeight ||
            elem.col < 0 || elem.col >= board[elem.row].length ||
            board[elem.row][elem.col] !== letter) {
            continue;
        }
        
        seen.add(key);
        
        if (elem.row === boardHeight - 1) {
            return true;
        }
        
        for (const diff of directions) {
            queue.push({row: elem.row + diff.dr, col: elem.col + diff.dc});
        }
    }
    
    return false;
}

class Board {
    constructor(board) {
        this.board = board.map(row => row.trim().split(' '));
    }

    winner() {
        if (has_path(this.board, 'O')) {
            return 'O';
        }
        if (has_path(transpose(this.board), 'X')) {
            return 'X';
        }
        return '';
    }
}

module.exports = Board;