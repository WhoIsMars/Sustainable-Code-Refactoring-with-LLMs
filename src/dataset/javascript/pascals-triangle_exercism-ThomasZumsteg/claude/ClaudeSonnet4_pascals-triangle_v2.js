var Triangle = function(nRows) {
	this.rows = [];
	if (nRows <= 0) return;
	
	var row = [1];
	this.rows.push(row);
	this.lastRow = row;
	
	for(var i = 1; i < nRows; i++) {
		var newRow = new Array(i + 1);
		newRow[0] = 1;
		newRow[i] = 1;
		
		for(var j = 1; j < i; j++) {
			newRow[j] = row[j-1] + row[j];
		}
		
		this.rows.push(newRow);
		this.lastRow = newRow;
		row = newRow;
	}
}

module.exports = Triangle;