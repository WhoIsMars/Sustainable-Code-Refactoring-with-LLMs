function accumulate(items, func) {
	if (!items || items.length === 0) return [];
	
	const length = items.length;
	const modified = new Array(length);
	
	for (let i = 0; i < length; i++) {
		modified[i] = func(items[i]);
	}
	
	return modified;
}

module.exports = accumulate;