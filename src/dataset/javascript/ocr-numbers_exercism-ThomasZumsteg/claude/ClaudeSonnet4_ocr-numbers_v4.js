function convert(OCR_string) {
	const OCR_lines = OCR_string.split("\n");
	const OCR_characters = [];
	const linesLength = OCR_lines.length;
	
	for(let line = 0; line < linesLength; line += 4) {
		OCR_characters.push(lines_to_characters(OCR_lines.slice(line, line + 4)));
	}

	const result = [];
	for(let i = 0; i < OCR_characters.length; i++) {
		const row = OCR_characters[i];
		const rowResult = [];
		for(let j = 0; j < row.length; j++) {
			const digit = OCR_digit_map.get(row[j]);
			rowResult.push(digit !== undefined ? digit : "?");
		}
		result.push(rowResult.join(""));
	}
	return result.join(",");
}

function lines_to_characters(line) {
	const characters = [];
	const numChars = Math.floor(line[0].length / 3);
	
	for(let c = 0; c < numChars; c++) {
		const charLines = [];
		const startPos = c * 3;
		const endPos = startPos + 3;
		
		for(let i = 0; i < line.length; i++) {
			charLines.push(line[i].slice(startPos, endPos));
		}
		characters.push(charLines.join("\n"));
	}
	return characters;
}

module.exports = {convert: convert};

const OCR_digit_map = new Map([
	[" _ \n| |\n|_|\n   ", "0"],
	["   \n  |\n  |\n   ", "1"],
	[" _ \n _|\n|_ \n   ", "2"],
	[" _ \n _|\n _|\n   ", "3"],
	["   \n|_|\n  |\n   ", "4"],
	[" _ \n|_ \n _|\n   ", "5"],
	[" _ \n|_ \n|_|\n   ", "6"],
	[" _ \n  |\n  |\n   ", "7"],
	[" _ \n|_|\n|_|\n   ", "8"],
	[" _ \n|_|\n _|\n   ", "9"]
]);