var Matrix = function(matrix) {
	/* A 2d matrix class */
	const splitRows = matrix.split("\n");
	const numRows = splitRows.length;
	const rows = new Array(numRows);
	
	// Parse rows once and cache first row length
	for (let i = 0; i < numRows; i++) {
		const splitCols = splitRows[i].split(" ");
		const numCols = splitCols.length;
		rows[i] = new Array(numCols);
		for (let j = 0; j < numCols; j++) {
			rows[i][j] = parseInt(splitCols[j], 10);
		}
	}
	
	this.rows = rows;
	
	// Build columns efficiently using pre-allocated arrays
	const numCols = rows[0].length;
	const columns = new Array(numCols);
	
	for (let col = 0; col < numCols; col++) {
		columns[col] = new Array(numRows);
		for (let row = 0; row < numRows; row++) {
			columns[col][row] = rows[row][col];
		}
	}
	
	this.columns = columns;
}

module.exports = Matrix;