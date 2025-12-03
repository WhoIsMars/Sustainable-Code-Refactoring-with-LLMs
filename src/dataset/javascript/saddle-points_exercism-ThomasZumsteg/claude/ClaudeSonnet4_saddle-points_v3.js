var Matrix = function(matrix) {
	this.rows = matrix.split("\n").map(function(row) { 
		return row.replace(/^\s+|\s+$/g,'').split(' ')
			.map(function(e) { return parseInt(e, 10)});
	});

	const numRows = this.rows.length;
	const numCols = this.rows[0].length;
	
	this.columns = new Array(numCols);
	for (let col = 0; col < numCols; col++) {
		this.columns[col] = new Array(numRows);
		for (let row = 0; row < numRows; row++) {
			this.columns[col][row] = this.rows[row][col];
		}
	}
	
	this.saddlePoints = saddlePoints(this);
}

function saddlePoints(matrix) {
	const numRows = matrix.rows.length;
	const numCols = matrix.columns.length;
	
	const row_max = new Array(numRows);
	for (let i = 0; i < numRows; i++) {
		let max = matrix.rows[i][0];
		for (let j = 1; j < matrix.rows[i].length; j++) {
			if (matrix.rows[i][j] > max) {
				max = matrix.rows[i][j];
			}
		}
		row_max[i] = max;
	}
	
	const column_min = new Array(numCols);
	for (let i = 0; i < numCols; i++) {
		let min = matrix.columns[i][0];
		for (let j = 1; j < matrix.columns[i].length; j++) {
			if (matrix.columns[i][j] < min) {
				min = matrix.columns[i][j];
			}
		}
		column_min[i] = min;
	}
	
	const saddlePoints = [];
	for (let r = 0; r < numRows; r++) {
		for (let c = 0; c < numCols; c++) {
			const element = matrix.rows[r][c];
			if (element === row_max[r] && element === column_min[c]) {
				saddlePoints.push([r, c]);
			}
		}
	}
	
	return saddlePoints;
}

module.exports = Matrix;