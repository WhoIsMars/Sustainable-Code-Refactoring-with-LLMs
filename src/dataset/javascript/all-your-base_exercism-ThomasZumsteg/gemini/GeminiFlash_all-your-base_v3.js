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
        for (let i = 0; i < digits.length; i++) {
            const digit = digits[i];
            if (!Number.isInteger(digit) || digit < 0 || from <= digit) {
                throw new Error('Input has wrong format');
            }
            total = total * from + digit;
        }

        const result = [];
        if (total === 0) {
            return [0];
        }

        while (total > 0) {
            result.unshift(total % to);
            total = Math.floor(total / to);
        }

        return result;
    }
}

module.exports = Converter;