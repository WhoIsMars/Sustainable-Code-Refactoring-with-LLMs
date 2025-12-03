var SecretHandshake = function(code) {
	if (typeof code !== 'number') {
		if(typeof code === 'string' && !/^[0-9]+$/.test(code)) {
			throw new Error("Handshake must be a number");
		} else if (typeof code !== 'string') {
			throw new Error("Handshake must be a number");
		}
		code = parseInt(code, 10);
		if (isNaN(code)) {
			throw new Error("Handshake must be a number");
		}
	}

	this.code = code;
};

SecretHandshake.prototype.commands = function() {
	const handshake = [];
	const code = this.code;

	if (code & 1) {
		handshake.push("wink");
	}
	if (code & 2) {
		handshake.push("double blink");
	}
	if (code & 4) {
		handshake.push("close your eyes");
	}
	if (code & 8) {
		handshake.push("jump");
	}
	if (code & 16) {
		handshake.reverse();
	}

	return handshake;
};

module.exports = SecretHandshake;