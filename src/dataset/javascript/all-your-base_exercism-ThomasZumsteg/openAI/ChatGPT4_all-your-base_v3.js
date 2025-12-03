class Converter {
    convert(digits, from, to) {
        if (!Number.isInteger(from) || from <= 1) {
            throw new Error('Wrong input base');
        }
        if (!Number.isInteger(to) || to <= 1) {
            throw new Error('Wrong output base');
        }
        if (digits.length === 0 || (digits.length > 1 && digits[0] === 0)) {
            throw new Error('Input has wrong format');
        }

        let total = 0;
        for (const digit of digits) {
            if (digit < 0 || digit >= from) {
                throw new Error('Input has wrong format');
            }
            total = total * from + digit;
        }

        if (total === 0) return [0];

        const result = [];
        while (total > 0) {
            result.push(total % to);
            total = Math.floor(total / to);
        }
        return result.reverse();
    }
}

module.exports = Converter;