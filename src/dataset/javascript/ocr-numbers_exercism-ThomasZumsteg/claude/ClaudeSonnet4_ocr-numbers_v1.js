function convert(OCR_string) {
	/* Convert a line representation of digits into a string of digits */
	const OCR_lines = OCR_string.split("\n");
	const OCR_characters = [];
	const OCR_lines_length = OCR_lines.length;
	
	for(let line = 0; line < OCR_lines_length; line += 4) {
		OCR_characters.push(lines_to_characters(OCR_lines.slice(line, line + 4)));
	}

	const results = [];
	for(let i = 0; i < OCR_characters.length; i++) {
		const row = OCR_characters[i];
		const rowResults = [];
		for(let j = 0; j < row.length; j++) {
			const digit = OCR_digit_map.get(row[j]);
			rowResults.push(digit !== undefined ? digit : "?");
		}
		results.push(rowResults.join(""));
	}
	return results.join(",");
}

function lines_to_characters(line) {
	/* Divides a set of lines into characters */
	const characters = [];
	const numChars = line[0].length / 3;
	
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

const OCR_digits = [
	" _ \n" +
	"| |\n" +
	"|_|\n" +
	"   ",
    "   \n" +
    "  |\n" +
    "  |\n" +
    "   ",
    " _ \n" +
    " _|\n" +
    "|_ \n" +
    "   ",      
    " _ \n" +
    " _|\n" +
    " _|\n" +
    "   ",
    "   \n" +
    "|_|\n" +
    "  |\n" +
    "   ",
    " _ \n" +
    "|_ \n" +
    " _|\n" +
    "   ",
    " _ \n" +
    "|_ \n" +
    "|_|\n" +
    "   ",
    " _ \n" +
    "  |\n" +
    "  |\n" +
    "   ",
    " _ \n" +
    "|_|\n" +
    "|_|\n" +
    "   ",
    " _ \n" +
    "|_|\n" +
    " _|\n" +
    "   ",
];

const OCR_digit_map = new Map();
for(let i = 0; i < OCR_digits.length; i++) {
	OCR_digit_map.set(OCR_digits[i], i.toString());
}