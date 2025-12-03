var SecretHandshake = function(code) {
    if (typeof code !== 'number') {
        throw new Error("Handshake must be a number");
    }
    this.code = code;
};

SecretHandshake.prototype.commands = function() {
    const handshake = [];
    if (this.code & 1) {
        handshake.push("wink");
    }
    if (this.code & 2) {
        handshake.push("double blink");
    }
    if (this.code & 4) {
        handshake.push("close your eyes");
    }
    if (this.code & 8) {
        handshake.push("jump");
    }
    if (this.code & 16) {
        handshake.reverse();
    }
    return handshake;
};

module.exports = SecretHandshake;