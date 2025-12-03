const ones = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
const teens = ["", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"];
const tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"];
const powers = ["", " thousand", " million", " billion"];

function inEnglish(num) {
  if (num < 0 || num >= 1000000000000) {
    throw new Error('Number must be between 0 and 999,999,999,999.');
  }

  if (num === 0) {
    return "zero";
  }

  let english = "";
  let power = 0;

  while (num > 0) {
    const group = num % 1000;
    if (group > 0) {
      english = englishPower(group) + powers[power] + (english ? " " : "") + english;
    }
    num = Math.floor(num / 1000);
    power++;
  }

  return english;
}

function englishPower(digits) {
  let english = "";
  const hundred = Math.floor(digits / 100);
  const remainder = digits % 100;

  if (hundred > 0) {
    english += ones[hundred] + " hundred";
  }

  if (remainder > 0) {
    if (english !== "") {
      english += " ";
    }

    if (remainder < 10) {
      english += ones[remainder];
    } else if (remainder < 20) {
      english += teens[remainder - 10];
    } else {
      const ten = Math.floor(remainder / 10);
      const one = remainder % 10;
      english += tens[ten];
      if (one > 0) {
        english += "-" + ones[one];
      }
    }
  }

  return english;
}

module.exports = { inEnglish: inEnglish };