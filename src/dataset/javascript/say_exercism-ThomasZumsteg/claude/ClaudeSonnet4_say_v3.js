const ones = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine'];
const teens = ['', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen'];
const tens = ['', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety'];
const powers = ['', ' thousand', ' million', ' billion'];

function inEnglish(num) {
	if (num < 0 || num >= 1000000000000) {
		throw new Error('Number must be between 0 and 999,999,999,999.');
	}

	if (num === 0) return 'zero';

	const parts = [];
	let power = 0;
	
	while (num > 0) {
		const group = num % 1000;
		if (group !== 0) {
			const groupText = englishPower(group);
			parts.unshift(groupText + powers[power]);
		}
		num = Math.floor(num / 1000);
		power++;
	}
	
	return parts.join(' ');
}

function englishPower(digits) {
	const hundreds = Math.floor(digits / 100);
	const remainder = digits % 100;
	const tensDigit = Math.floor(remainder / 10);
	const onesDigit = remainder % 10;
	
	let result = '';
	
	if (hundreds > 0) {
		result = ones[hundreds] + ' hundred';
	}
	
	if (tensDigit === 1) {
		result += (result ? ' ' : '') + teens[onesDigit];
	} else {
		if (tensDigit > 0) {
			result += (result ? ' ' : '') + tens[tensDigit];
		}
		if (onesDigit > 0) {
			result += (result ? (tensDigit > 0 ? '-' : ' ') : '') + ones[onesDigit];
		}
	}
	
	return result;
}

module.exports = {inEnglish: inEnglish};