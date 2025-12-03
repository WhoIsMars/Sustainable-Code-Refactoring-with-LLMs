function factors(number) {
    if (number <= 1) {
        return [];
    }

    const result = [1];
    for (let f = 2; f * f <= number; f++) {
        if (number % f === 0) {
            result.push(f);
            const quotient = number / f;
            if (quotient !== f) {
                result.push(quotient);
            }
        }
    }
    return result.sort((a, b) => a - b);
}

class PerfectNumbers {
    classify(number) {
        if (number <= 0) {
            return "Classification is only possible for natural numbers.";
        }

        let factorSum = 0;
        for (let f = 1; f * f <= number; f++) {
            if (number % f === 0) {
                if (f * f !== number) {
                    if (f !== number) {
                        factorSum += f;
                    }
                    const quotient = number / f;
                    if (quotient !== number) {
                        factorSum += quotient;
                    }
                } else {
                    if (f !== number) {
                        factorSum += f;
                    }
                }
            }
        }

        if (number < factorSum) {
            return "abundant";
        } else if (number > factorSum) {
            return "deficient";
        } else {
            return "perfect";
        }
    }
}

module.exports = PerfectNumbers;