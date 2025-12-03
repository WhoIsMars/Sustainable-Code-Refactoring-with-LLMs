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

    let digit_groups = [];
    while (num > 0) {
        digit_groups.push(num % 1000);
        num = Math.floor(num / 1000);
    }

    let english = "";
    for (let i = digit_groups.length - 1; i >= 0; i--) {
        const group = digit_groups[i];
        if (group !== 0) {
            const groupEnglish = englishPower(group);
            english += groupEnglish + powers[i];
            if (i > 0 && english.length > groupEnglish.length + powers[i].length) {
                english += " ";
            }
        }
    }

    return english;
}

function englishPower(digits) {
    let english = "";
    const hundreds = Math.floor(digits / 100);
    const remainder = digits % 100;
    const tensDigit = Math.floor(remainder / 10);
    const onesDigit = remainder % 10;

    if (hundreds !== 0) {
        english += ones[hundreds] + " hundred";
    }

    if (tensDigit === 1) {
        if (english) {
            english += " ";
        }
        english += teens[onesDigit];
        return english;
    } else {
        if (tensDigit !== 0) {
            if (english) {
                english += " ";
            }
            english += tens[tensDigit];
        }

        if (onesDigit !== 0) {
            if (english) {
                english += tensDigit > 0 ? '-' : ' ';
            }
            english += ones[onesDigit];
        }
    }

    return english;
}

module.exports = { inEnglish: inEnglish };