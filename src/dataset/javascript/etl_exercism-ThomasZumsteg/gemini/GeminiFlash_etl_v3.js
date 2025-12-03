var ETL = function() {}

ETL.prototype.transform = function(oldSturct) {
	var newStruct = {};
	for (const key in oldSturct) {
		if (Object.hasOwn(oldSturct, key)) {
			const values = oldSturct[key];
			const parsedKey = parseInt(key);
			for (let i = 0; i < values.length; i++) {
				newStruct[values[i].toLowerCase()] = parsedKey;
			}
		}
	}
	return newStruct;
}

module.exports = ETL