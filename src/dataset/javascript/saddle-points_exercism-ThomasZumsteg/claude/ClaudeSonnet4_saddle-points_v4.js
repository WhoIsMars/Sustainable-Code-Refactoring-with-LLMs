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
	const numCols = matrix.rows[0].length;
	
	const row_max = new Array(numRows);
	for (let r = 0; r < numRows; r++) {
		let max = matrix.rows[r][0];
		for (let c = 1; c < numCols; c++) {
			if (matrix.rows[r][c] > max) {
				max = matrix.rows[r][c];
			}
		}
		row_max[r] = max;
	}
	
	const column_min = new Array(numCols);
	for (let c = 0; c < numCols; c++) {
		let min = matrix.columns[c][0];
		for (let r = 1; r < numRows; r++) {
			if (matrix.columns[c][r] < min) {
				min = matrix.columns[c][r];
			}
		}
		column_min[c] = min;
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