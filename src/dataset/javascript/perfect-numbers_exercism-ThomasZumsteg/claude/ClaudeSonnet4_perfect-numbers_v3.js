function factors(number) {
    if (number === 1) return [];
    
    const result = [1];
    const sqrt = Math.sqrt(number);
    
    for (let f = 2; f <= sqrt; f++) {
        if (number % f === 0) {
            result.push(f);
            if (f !== sqrt) {
                result.push(number / f);
            }
        }
    }
    
    return result;
}

class PerfectNumbers {
    classify(number) {
        if (number <= 0) {
            return "Classification is only possible for natural numbers.";
        }

        let factorSum = 1;
        const sqrt = Math.sqrt(number);
        
        for (let f = 2; f <= sqrt; f++) {
            if (number % f === 0) {
                factorSum += f;
                if (f !== sqrt) {
                    factorSum += number / f;
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