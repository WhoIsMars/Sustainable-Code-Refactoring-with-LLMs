var bigInt = (function () {
    'use strict';

    const BASE = 1e7;
    const LOG_BASE = Math.log(BASE);
    const MAX_INT = 9007199254740992;
    const MAX_INT_ARR = [MAX_INT % BASE, Math.floor(MAX_INT / BASE)];
    const SMALL = 1e7;

    function BigInt(value, sign) {
        this.value = value;
        this.sign = sign;
        this.isSmall = false;
    }

    function SmallInt(value) {
        this.value = value;
        this.sign = value < 0;
        this.isSmall = true;
    }

    function isSmall(value) {
        return -SMALL < value && value < SMALL;
    }

    function parseValue(value) {
        if (value instanceof BigInt || value instanceof SmallInt) return value;
        if (typeof value === 'number') {
            if (isSmall(value)) return new SmallInt(value);
            value = String(value);
        }
        if (typeof value === 'string') {
            const sign = value[0] === '-';
            if (sign) value = value.slice(1);
            const parts = value.split(/e/i);
            if (parts.length > 2) throw new Error('Invalid integer: ' + value);
            if (parts.length === 2) {
                let exp = +parts[1];
                if (exp !== Math.floor(exp) || !isFinite(exp)) throw new Error('Invalid integer: ' + value);
                let base = parts[0];
                const dotIndex = base.indexOf('.');
                if (dotIndex >= 0) {
                    exp -= base.length - dotIndex - 1;
                    base = base.replace('.', '');
                }
                if (exp < 0) throw new Error('Negative exponent not allowed for integers');
                value = base + '0'.repeat(exp);
            }
            const digits = [];
            for (let i = value.length; i > 0; i -= 7) {
                digits.push(+value.substring(Math.max(0, i - 7), i));
            }
            return new BigInt(digits, sign);
        }
        throw new Error('Invalid value: ' + value);
    }

    function addArrays(a, b) {
        const length = Math.max(a.length, b.length);
        const result = new Array(length);
        let carry = 0;
        for (let i = 0; i < length || carry; i++) {
            const sum = (a[i] || 0) + (b[i] || 0) + carry;
            result[i] = sum % BASE;
            carry = Math.floor(sum / BASE);
        }
        return result;
    }

    function subtractArrays(a, b) {
        const result = [];
        let borrow = 0;
        for (let i = 0; i < a.length; i++) {
            let diff = a[i] - (b[i] || 0) - borrow;
            if (diff < 0) {
                diff += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }
            result.push(diff);
        }
        return result;
    }

    function multiplyArrays(a, b) {
        const result = new Array(a.length + b.length).fill(0);
        for (let i = 0; i < a.length; i++) {
            let carry = 0;
            for (let j = 0; j < b.length || carry; j++) {
                const product = result[i + j] + a[i] * (b[j] || 0) + carry;
                result[i + j] = product % BASE;
                carry = Math.floor(product / BASE);
            }
        }
        return result;
    }

    function divideArrays(a, b) {
        if (b.length === 1 && b[0] === 0) throw new Error('Division by zero');
        const result = [];
        let remainder = [];
        for (let i = a.length - 1; i >= 0; i--) {
            remainder.unshift(a[i]);
            let quotient = 0;
            while (compareArrays(remainder, b) >= 0) {
                remainder = subtractArrays(remainder, b);
                quotient++;
            }
            result.unshift(quotient);
        }
        return [result, remainder];
    }

    function compareArrays(a, b) {
        if (a.length !== b.length) return a.length > b.length ? 1 : -1;
        for (let i = a.length - 1; i >= 0; i--) {
            if (a[i] !== b[i]) return a[i] > b[i] ? 1 : -1;
        }
        return 0;
    }

    function trimArray(arr) {
        while (arr.length > 1 && arr[arr.length - 1] === 0) arr.pop();
        return arr;
    }

    BigInt.prototype.add = function (other) {
        const o = parseValue(other);
        if (this.sign !== o.sign) return this.subtract(o.negate());
        return new BigInt(addArrays(this.value, o.value), this.sign);
    };

    BigInt.prototype.subtract = function (other) {
        const o = parseValue(other);
        if (this.sign !== o.sign) return this.add(o.negate());
        const cmp = compareArrays(this.value, o.value);
        if (cmp === 0) return new SmallInt(0);
        const result = cmp > 0 ? subtractArrays(this.value, o.value) : subtractArrays(o.value, this.value);
        return new BigInt(trimArray(result), cmp < 0 ? !this.sign : this.sign);
    };

    BigInt.prototype.multiply = function (other) {
        const o = parseValue(other);
        if (this.isSmall && o.isSmall) {
            const product = this.value * o.value;
            return isSmall(product) ? new SmallInt(product) : new BigInt(multiplyArrays([Math.abs(this.value)], [Math.abs(o.value)]), this.sign !== o.sign);
        }
        return new BigInt(multiplyArrays(this.value, o.value), this.sign !== o.sign);
    };

    BigInt.prototype.divide = function (other) {
        const o = parseValue(other);
        const [quotient] = divideArrays(this.value, o.value);
        return new BigInt(trimArray(quotient), this.sign !== o.sign);
    };

    BigInt.prototype.mod = function (other) {
        const o = parseValue(other);
        const [, remainder] = divideArrays(this.value, o.value);
        return new BigInt(trimArray(remainder), this.sign);
    };

    return function (value) {
        return parseValue(value);
    };
})();