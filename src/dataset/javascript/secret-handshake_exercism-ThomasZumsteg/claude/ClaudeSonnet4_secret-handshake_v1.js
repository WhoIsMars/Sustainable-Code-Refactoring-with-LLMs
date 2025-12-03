var SecretHandshake = function(code) {
	/* Creates a secret handshake based on the Mary Poppins code */
	if(typeof code !== 'number' || !Number.isInteger(code) || code < 0)
		throw new Error("Handshake must be a number");
	this.code = code;
}

SecretHandshake.prototype.commands = function() {
	/* Encodes the handshake */
	var handshake = [];
	var code = this.code;
	
	if(code & 1) handshake.push("wink");
	if(code & 2) handshake.push("double blink");
	if(code & 4) handshake.push("close your eyes");
	if(code & 8) handshake.push("jump");
	if(code & 16) handshake.reverse();
	
	return handshake;
};

module.exports = SecretHandshake;