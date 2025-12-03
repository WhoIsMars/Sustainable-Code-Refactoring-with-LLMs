class SecretHandshake {
	constructor(code) {
		if (!Number.isInteger(code)) throw new Error("Handshake must be a number");
		this.code = code;
		this.handshakeSteps = [
			"wink",
			"double blink",
			"close your eyes",
			"jump"
		];
	}

	commands() {
		const handshake = [];
		for (let i = 0; i < this.handshakeSteps.length; i++) {
			if (this.code & (1 << i)) handshake.push(this.handshakeSteps[i]);
		}
		return (this.code & 16) ? handshake.reverse() : handshake;
	}
}

module.exports = SecretHandshake;