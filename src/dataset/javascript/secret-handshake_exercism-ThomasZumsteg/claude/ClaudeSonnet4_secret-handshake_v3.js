var SecretHandshake = function(code) {
	if (typeof code !== 'number' || !Number.isInteger(code) || code < 0) {
		throw new Error("Handshake must be a number");
	}
	this.code = code;
};

SecretHandshake.prototype.commands = function() {
	const actions = ["wink", "double blink", "close your eyes", "jump"];
	const result = [];
	
	for (let i = 0; i < 4; i++) {
		if (this.code & (1 << i)) {
			result.push(actions[i]);
		}
	}
	
	return (this.code & 16) ? result.reverse() : result;
};

module.exports = SecretHandshake;