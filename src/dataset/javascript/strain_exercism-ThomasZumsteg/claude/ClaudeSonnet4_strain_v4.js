module.exports = {
	keep: keep,
	discard: discard,
}

function keep(items, func) {
	const result = [];
	const length = items.length;
	for (let i = 0; i < length; i++) {
		if (func(items[i])) {
			result.push(items[i]);
		}
	}
	return result;
}

function discard(items, func) {
	const result = [];
	const length = items.length;
	for (let i = 0; i < length; i++) {
		if (!func(items[i])) {
			result.push(items[i]);
		}
	}
	return result;
}