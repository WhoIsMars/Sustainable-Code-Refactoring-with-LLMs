class Queens {
	constructor(args) {
		this.white = (args?.white) || [0, 3];
		this.black = (args?.black) || [7, 3];
		if (this.white[0] === this.black[0] && this.white[1] === this.black[1]) {
			throw new Error("Queens cannot share the same space");
		}
	}

	toString() {
		const board = Array.from({ length: 8 }, (_, i) =>
			Array.from({ length: 8 }, (_, j) =>
				this.white[0] === i && this.white[1] === j
					? "W"
					: this.black[0] === i && this.black[1] === j
					? "B"
					: "_"
			).join(" ")
		);
		return board.join("\n") + "\n";
	}

	canAttack() {
		const [dx, dy] = [Math.abs(this.black[0] - this.white[0]), Math.abs(this.black[1] - this.white[1])];
		return dx === 0 || dy === 0 || dx === dy;
	}
}

module.exports = Queens;