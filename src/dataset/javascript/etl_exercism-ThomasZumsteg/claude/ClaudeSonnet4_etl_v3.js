var ETL = function() {}

ETL.prototype.transform = function(oldSturct) {
	var newStruct = {};
	var keyInt, values, i, len;
	
	for (var key in oldSturct) {
		if (oldSturct.hasOwnProperty(key)) {
			keyInt = parseInt(key, 10);
			values = oldSturct[key];
			
			for (i = 0, len = values.length; i < len; i++) {
				newStruct[values[i].toLowerCase()] = keyInt;
			}
		}
	}
	
	return newStruct;
}

module.exports = ETL