var Matrix = function(matrix) {
    /* A 2d matrix class */
    const rows = matrix.split("\n");
    this.rows = rows.map(row => {
        return row.split(" ").map(e => parseInt(e, 10));
    });

    const numCols = this.rows[0].length;
    this.columns = Array(numCols).fill(null).map((_, colNum) => {
        return this.rows.map(row => row[colNum]);
    });
};

module.exports = Matrix;