function accumulate(items, func) {
	var modified = new Array(items.length);
	for (var i = 0; i < items.length; i++) {
		modified[i] = func(items[i]);
	}
	return modified;
}

module.exports = accumulate;