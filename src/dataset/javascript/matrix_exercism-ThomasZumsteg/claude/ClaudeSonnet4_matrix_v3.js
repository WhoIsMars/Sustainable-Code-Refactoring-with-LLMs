var Matrix = function(matrix) {
    const rowStrings = matrix.split("\n");
    const numRows = rowStrings.length;
    const numCols = rowStrings[0].split(" ").length;
    
    this.rows = new Array(numRows);
    for (let i = 0; i < numRows; i++) {
        const rowElements = rowStrings[i].split(" ");
        this.rows[i] = new Array(numCols);
        for (let j = 0; j < numCols; j++) {
            this.rows[i][j] = parseInt(rowElements[j], 10);
        }
    }

    this.columns = new Array(numCols);
    for (let colNum = 0; colNum < numCols; colNum++) {
        this.columns[colNum] = new Array(numRows);
        for (let rowNum = 0; rowNum < numRows; rowNum++) {
            this.columns[colNum][rowNum] = this.rows[rowNum][colNum];
        }
    }
};

module.exports = Matrix;