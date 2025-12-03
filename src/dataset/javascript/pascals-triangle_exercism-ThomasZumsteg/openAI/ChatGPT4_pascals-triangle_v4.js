class Triangle {
    constructor(nRows) {
        this.rows = [];
        let row = [1];
        for (let i = 0; i < nRows; i++) {
            this.rows.push(row);
            this.lastRow = row;
            row = this._nextRow(row);
        }
    }

    _nextRow(currentRow) {
        const row = new Array(currentRow.length + 1);
        row[0] = 1;
        for (let j = 1; j < currentRow.length; j++) {
            row[j] = currentRow[j - 1] + currentRow[j];
        }
        row[currentRow.length] = 1;
        return row;
    }
}

module.exports = Triangle;