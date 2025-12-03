var Matrix = function(matrix) {
	/* Two dimensional matrix class */
	this.rows = matrix.split("\n").map(function(row) { 
		return row.replace(/^\s+|\s+$/g,'').split(' ')
			.map(function(e) { return parseInt(e, 10)});
	});

	var numCols = this.rows[0].length;
	this.columns = new Array(numCols);
	for (var col = 0; col < numCols; col++) {
		this.columns[col] = new Array(this.rows.length);
		for (var row = 0; row < this.rows.length; row++) {
			this.columns[col][row] = this.rows[row][col];
		}
	}
	
	this.saddlePoints = saddlePoints(this);
}

function saddlePoints(matrix) {
	/* Finds saddle points in a matrix */
	var numRows = matrix.rows.length;
	var numCols = matrix.columns.length;
	
	var row_max = new Array(numRows);
	for (var r = 0; r < numRows; r++) {
		var max = matrix.rows[r][0];
		for (var c = 1; c < matrix.rows[r].length; c++) {
			if (matrix.rows[r][c] > max) {
				max = matrix.rows[r][c];
			}
		}
		row_max[r] = max;
	}
	
	var column_min = new Array(numCols);
	for (var c = 0; c < numCols; c++) {
		var min = matrix.columns[c][0];
		for (var r = 1; r < matrix.columns[c].length; r++) {
			if (matrix.columns[c][r] < min) {
				min = matrix.columns[c][r];
			}
		}
		column_min[c] = min;
	}
	
	var saddlePoints = [];
	for (var r = 0; r < numRows; r++) {
		for (var c = 0; c < matrix.rows[r].length; c++) {
			var element = matrix.rows[r][c];
			if (element === row_max[r] && element === column_min[c]) {
				saddlePoints.push([r, c]);
			}
		}
	}
	
	return saddlePoints;
};

module.exports = Matrix;