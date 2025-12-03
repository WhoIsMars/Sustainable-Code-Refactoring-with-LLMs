class Converter {
    convert(digits, from, to) {
        if (from == null || from <= 1 || from !== Math.floor(from)) {
            throw new Error('Wrong input base');
        }
        if (to == null || to <= 1 || to !== Math.floor(to)) {
            throw new Error('Wrong output base');
        }
        if (digits.length === 0 || (digits.length > 1 && digits[0] === 0)) {
            throw new Error('Input has wrong format');
        }

        let total = 0;
        for (let i = 0; i < digits.length; i++) {
            const digit = digits[i];
            if (digit < 0 || digit >= from) {
                throw new Error('Input has wrong format');
            }
            total = total * from + digit;
        }

        if (total === 0) {
            return [0];
        }

        const result = [];
        while (total > 0) {
            result.push(total % to);
            total = Math.floor(total / to);
        }
        
        return result.reverse();
    }
}

module.exports = Converter;