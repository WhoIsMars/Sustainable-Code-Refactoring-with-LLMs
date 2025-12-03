function convert(OCR_string) {
  const OCR_lines = OCR_string.split("\n");
  const OCR_characters = [];
  for (let line = 0; line < OCR_lines.length; line += 4) {
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

function lines_to_characters(OCR_lines, lineStart) {
  const line = OCR_lines.slice(lineStart, lineStart + 4);
  const characters = [];
  const charCount = line[0].length / 3;

  for (let c = 0; c < charCount; c++) {
    let characterLines = "";
    for (let i = 0; i < 4; i++) {
      characterLines += line[i].slice(c * 3, c * 3 + 3);
      if (i < 3) {
        characterLines += "\n";
      }
    }
    characters.push(characterLines);
  }
  return characters;
}

module.exports = { convert: convert };

const OCR_digits = [
  " _ \n" + "|||\n" + "|||\n" + "   ",
  "   \n" + "  |\n" + "  |\n" + "   ",
  " _ \n" + "_|\n" + "|_ \n" + "   ",
  " _ \n" + "_|\n" + " _|\n" + "   ",
  "   \n" + "|_|\n" + "  |\n" + "   ",
  " _ \n" + "|_ \n" + " _|\n" + "   ",
  " _ \n" + "|_ \n" + "|||\n" + "   ",
  " _ \n" + "  |\n" + "  |\n" + "   ",
  " _ \n" + "|||\n" + "|||\n" + "   ",
  " _ \n" + "|||\n" + " _|\n" + "   ",
];