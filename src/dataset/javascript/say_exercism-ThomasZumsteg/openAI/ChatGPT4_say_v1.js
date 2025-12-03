const ones = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
const teens = ["", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"];
const tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"];
const powers = ["", " thousand", " million", " billion"];

function inEnglish(num) {
    if (num < 0 || num >= 1e12) throw new Error('Number must be between 0 and 999,999,999,999.');
    if (num === 0) return "zero";

    const digitGroups = [];
    while (num > 0) {
        digitGroups.push(num % 1000);
        num = Math.floor(num / 1000);
    }

    return digitGroups
        .map((group, power) => group ? englishPower(group) + powers[power] : '')
        .filter(Boolean)
        .reverse()
        .join(' ');
}

function englishPower(digits) {
    const [hundreds, tensDigit, onesDigit] = ("00" + digits).slice(-3).split('').map(Number);
    let english = "";

    if (hundreds) english += ones[hundreds] + " hundred";
    if (tensDigit === 1 && onesDigit !== 0) {
        return english + (english ? ' ' : '') + teens[onesDigit];
    }
    if (tensDigit) english += (english ? ' ' : '') + tens[tensDigit];
    if (onesDigit) english += (english && tensDigit ? '-' : english ? ' ' : '') + ones[onesDigit];

    return english;
}

module.exports = { inEnglish };