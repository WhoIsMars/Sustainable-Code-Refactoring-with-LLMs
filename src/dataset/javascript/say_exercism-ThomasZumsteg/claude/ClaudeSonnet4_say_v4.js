const ones = ['', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine'];
const teens = ['', 'eleven', 'twelve', 'thirteen', 'fourteen', 'fifteen', 'sixteen', 'seventeen', 'eighteen', 'nineteen'];
const tens = ['', '', 'twenty', 'thirty', 'forty', 'fifty', 'sixty', 'seventy', 'eighty', 'ninety'];
const powers = ['', ' thousand', ' million', ' billion'];

function inEnglish(num) {
	if (num < 0 || num >= 1000000000000) {
		throw new Error('Number must be between 0 and 999,999,999,999.');
	}

	if (num === 0) return 'zero';

	const groups = [];
	let remaining = num;
	while (remaining > 0) {
		groups.push(remaining % 1000);
		remaining = Math.floor(remaining / 1000);
	}
	
	let result = '';
	for (let i = groups.length - 1; i >= 0; i--) {
		const group = groups[i];
		if (group === 0) continue;
		
		const groupText = englishPower(group);
		result += groupText + powers[i];
		if (i > 0 && result) result += ' ';
	}
	
	return result.trim();
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