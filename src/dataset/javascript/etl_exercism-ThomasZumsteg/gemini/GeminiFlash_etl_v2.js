var ETL = function() {}

ETL.prototype.transform = function(oldSturct) {
	/* Converts an old data structure to a new format */
	const newStruct = {};
	for (const key in oldSturct) {
		if (oldSturct.hasOwnProperty(key)) {
			const values = oldSturct[key];
			const parsedKey = parseInt(key, 10); // Parse key once
			for (let i = 0; i < values.length; i++) {
				newStruct[values[i].toLowerCase()] = parsedKey;
			}
		}
	}
	return newStruct;
}

module.exports = ETL