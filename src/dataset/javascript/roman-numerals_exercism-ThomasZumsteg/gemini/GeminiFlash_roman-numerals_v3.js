/* Decimal to Roman numeral mapping */
var decToNum = {   1: "I",   4:"IV",   5: "V",   9:"IX",
				  10: "X",  40:"XL",  50: "L",  90:"XC",
				 100: "C", 400:"CD", 500: "D", 900:"CM",
				1000: "M",
				};

function toRoman(remainer) {
	/* Convert a decimal number to a roman numeral */
	let result = '';
	const decimalNumbers = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1];

	for (const decimal of decimalNumbers) {
		while (remainer >= decimal) {
			result += decToNum[decimal];
			remainer -= decimal;
		}
		if (remainer === 0) {
			break;
		}
	}

	return result;
};

module.exports = toRoman;