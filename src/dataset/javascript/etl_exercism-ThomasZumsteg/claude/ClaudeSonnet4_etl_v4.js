var ETL = function() {}

ETL.prototype.transform = function(oldSturct) {
	var newStruct = {};
	var keys = Object.keys(oldSturct);
	var keyInt, values, val;
	
	for (var i = 0; i < keys.length; i++) {
		keyInt = parseInt(keys[i]);
		values = oldSturct[keys[i]];
		
		for (var j = 0; j < values.length; j++) {
			val = values[j];
			newStruct[val.toLowerCase()] = keyInt;
		}
	}
	
	return newStruct;
}

module.exports = ETL