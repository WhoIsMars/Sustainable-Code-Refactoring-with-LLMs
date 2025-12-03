var Matrix = function(matrix) {
	/* A 2d matrix class */
	const rows = matrix.split("\n");
	const numRows = rows.length;
	let parsedRows = new Array(numRows);

	for (let i = 0; i < numRows; i++) {
		const row = rows[i];
		const elements = row.split(" ");
		const numCols = elements.length;
		let parsedRow = new Array(numCols);

		for (let j = 0; j < numCols; j++) {
			parsedRow[j] = parseInt(elements[j], 10);
		}
		parsedRows[i] = parsedRow;
	}

	this.rows = parsedRows;

	const numCols = this.rows[0].length;
	let columns = new Array(numCols);

	for (let j = 0; j < numCols; j++) {
		let column = new Array(numRows);
		for (let i = 0; i < numRows; i++) {
			column[i] = this.rows[i][j];
		}
		columns[j] = column;
	}

	this.columns = columns;
}

module.exports = Matrix;