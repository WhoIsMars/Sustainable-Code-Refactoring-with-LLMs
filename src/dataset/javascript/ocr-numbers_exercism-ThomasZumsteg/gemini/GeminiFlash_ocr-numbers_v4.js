function convert(OCR_string) {
  const OCR_lines = OCR_string.split("\n");
  const numLines = OCR_lines.length;
  const OCR_characters = [];

  for (let line = 0; line < numLines; line += 4) {
    OCR_characters.push(lines_to_characters(OCR_lines, line));
  }

  return OCR_characters
    .map((row) =>
      row
        .map((character) => {
          const digit = OCR_digits.indexOf(character);
          return digit !== -1 ? digit.toString() : "?";
        })
        .join("")
    )
    .join(",");
}

function lines_to_characters(lines, startLine) {
  const characters = [];
  const lineLength = lines[startLine].length;
  const numChars = lineLength / 3;

  for (let c = 0; c < numChars; c++) {
    let character = "";
    for (let i = 0; i < 4; i++) {
      character += lines[startLine + i].slice(c * 3, c * 3 + 3);
      if (i < 3) {
        character += "\n";
      }
    }
    characters.push(character);
  }
  return characters;
}

module.exports = { convert: convert };

const OCR_digits = [
  " _ \n" + "|||\n" + "|_|\n" + "   ",
  "   \n" + "  |\n" + "  |\n" + "   ",
  " _ \n" + " _|\n" + "|_ \n" + "   ",
  " _ \n" + " _|\n" + " _|\n" + "   ",
  "   \n" + "|_|\n" + "  |\n" + "   ",
  " _ \n" + "|_ \n" + " _|\n" + "   ",
  " _ \n" + "|_ \n" + "|_|\n" + "   ",
  " _ \n" + "  |\n" + "  |\n" + "   ",
  " _ \n" + "|_|\n" + "|_|\n" + "   ",
  " _ \n" + "|_|\n" + " _|\n" + "   ",
];