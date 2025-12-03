module.exports = {
	keep: keep,
	discard: discard,
};

function keep(items, func) {
	return items.filter(func);
}

function discard(items, func) {
	return items.filter(item => !func(item));
}