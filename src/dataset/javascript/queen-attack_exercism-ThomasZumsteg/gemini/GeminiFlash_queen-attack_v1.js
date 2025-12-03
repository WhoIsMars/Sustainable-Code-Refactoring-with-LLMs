var Queens = function(args) {
    this.white = (args && args.white) || [0, 3];
    this.black = (args && args.black) || [7, 3];

    if (this.white[0] === this.black[0] && this.white[1] === this.black[1]) {
        throw "Queens cannot share the same space";
    }
};

Queens.prototype.toString = function() {
    let board = '';
    for (let i = 0; i < 8; i++) {
        let row = '';
        for (let j = 0; j < 8; j++) {
            if (this.white[0] === i && this.white[1] === j) {
                row += 'W';
            } else if (this.black[0] === i && this.black[1] === j) {
                row += 'B';
            } else {
                row += '_';
            }
            row += ' ';
        }
        board += row.trimEnd() + '\n';
    }
    return board;
};


Queens.prototype.canAttack = function() {
    const whiteRow = this.white[0];
    const whiteCol = this.white[1];
    const blackRow = this.black[0];
    const blackCol = this.black[1];

    return (whiteRow === blackRow ||
            whiteCol === blackCol ||
            Math.abs(whiteRow - blackRow) === Math.abs(whiteCol - blackCol));
};

module.exports = Queens;