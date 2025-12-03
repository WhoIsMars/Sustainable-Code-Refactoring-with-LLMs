const ones = ["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
const teens = ["", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"];
const tens = ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"];
const powers = ["", " thousand", " million", " billion"];

function inEnglish(num) {
	if (num < 0 || num >= 1000000000000)
		throw new Error('Number must be between 0 and 999,999,999,999.');

	if (num === 0)
		return "zero";

	const digit_groups = [];
	while (num > 0) {
		digit_groups.push(num % 1000);
		num = Math.floor(num / 1000);
	}
	
	let result = '';
	for (let i = digit_groups.length - 1; i >= 0; i--) {
		const group = digit_groups[i];
		if (group !== 0) {
			const groupText = englishPower(group);
			result += (result ? ' ' : '') + groupText + powers[i];
		}
	}
	
	return result;
}

function englishPower(digits) {
	const hundreds = Math.floor(digits / 100);
	const remainder = digits % 100;
	const tensDigit = Math.floor(remainder / 10);
	const onesDigit = remainder % 10;
	
	let english = "";

	if (hundreds !== 0)
		english = ones[hundreds] + " hundred";
	
	if (tensDigit === 1) {
		english += (english ? ' ' : '') + teens[onesDigit];
	} else {
		if (tensDigit !== 0)
			english += (english ? ' ' : '') + tens[tensDigit];
		
		if (onesDigit !== 0)
			english += (english ? (tensDigit ? '-' : ' ') : '') + ones[onesDigit];
	}

	return english;
}

module.exports = {inEnglish: inEnglish}