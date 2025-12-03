var ones = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
var teens = ["", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"];
var tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"];
var powers = ["", " thousand", " million", " billion"];

function inEnglish(num) {
    if (num < 0 || num >= 1000000000000) {
        throw new Error('Number must be between 0 and 999,999,999,999.');
    }

    if (num === 0) {
        return "zero";
    }

    var digit_groups = [];
    while (num > 0) {
        digit_groups.push(num % 1000);
        num = Math.floor(num / 1000);
    }

    let result = "";
    for (let i = 0; i < digit_groups.length; i++) {
        const group = digit_groups[i];
        if (group !== 0) {
            result = englishPower(group) + powers[i] + (result ? ' ' : '') + result;
        }
    }
    return result;
}

function englishPower(digits) {
    let english = "";
    const hundred = Math.floor(digits / 100);
    const remainder = digits % 100;
    const ten = Math.floor(remainder / 10);
    const one = remainder % 10;

    if (hundred !== 0) {
        english += ones[hundred] + " hundred";
    }

    if (ten === 1) {
        english += (english ? ' ' : '') + teens[one];
        return english;
    } else if (ten !== 0) {
        english += (english ? ' ' : '') + tens[ten];
    }

    if (one !== 0) {
        english += (english ? (ten ? '-' : ' ') : '') + ones[one];
    }

    return english;
}

module.exports = { inEnglish: inEnglish };