module.exports = {
	keep: keep,
	discard: discard,
}

function keep(items, func) {
	/* Selects items for which a function is True */
	const kept = [];
	const length = items.length;
	for(let i = 0; i < length; i++) {
		if(func(items[i])) {
			kept.push(items[i]);
		}
	}
	return kept;
}

function discard(items, func) {
	/* Selects items for which a function is False */
	const kept = [];
	const length = items.length;
	for(let i = 0; i < length; i++) {
		if(!func(items[i])) {
			kept.push(items[i]);
		}
	}
	return kept;
}