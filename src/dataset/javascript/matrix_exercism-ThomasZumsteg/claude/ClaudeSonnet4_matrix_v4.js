var Matrix = function(matrix) {
	var splitRows = matrix.split("\n");
	var numRows = splitRows.length;
	var numCols = splitRows[0].split(" ").length;
	
	this.rows = new Array(numRows);
	for (var i = 0; i < numRows; i++) {
		var rowElements = splitRows[i].split(" ");
		this.rows[i] = new Array(numCols);
		for (var j = 0; j < numCols; j++) {
			this.rows[i][j] = parseInt(rowElements[j], 10);
		}
	}

	this.columns = new Array(numCols);
	for (var col = 0; col < numCols; col++) {
		this.columns[col] = new Array(numRows);
		for (var row = 0; row < numRows; row++) {
			this.columns[col][row] = this.rows[row][col];
		}
	}
};

module.exports = Matrix;