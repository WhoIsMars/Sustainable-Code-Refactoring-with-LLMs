var Matrix = function(matrix) {
    const rows = matrix.split("\n").map(row => row.split(" ").map(Number));
    const columns = Array.from({ length: rows[0].length }, (_, colNum) => rows.map(row => row[colNum]));
    this.rows = rows;
    this.columns = columns;
};

module.exports = Matrix;