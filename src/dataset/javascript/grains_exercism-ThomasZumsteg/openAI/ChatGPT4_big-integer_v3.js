var bigInt = (function () {
  'use strict';

  const BASE = 1e7;
  const LOG_BASE = 7;
  const MAX_INT = 9007199254740992;
  const BASE_MASK = BASE - 1;

  class BigInteger {
    constructor(value, sign) {
      this.value = value;
      this.sign = sign;
      this.isSmall = false;
    }
  }

  class SmallInteger {
    constructor(value) {
      this.value = value;
      this.sign = value < 0;
      this.isSmall = true;
    }
  }

  function isSmall(num) {
    return -MAX_INT < num && num < MAX_INT;
  }

  function parseValue(value) {
    if (value instanceof BigInteger || value instanceof SmallInteger) return value;
    if (typeof value === 'number') {
      if (isSmall(value)) return new SmallInteger(value);
      value = value.toString();
    }
    if (typeof value === 'string') {
      const sign = value[0] === '-';
      if (sign) value = value.slice(1);
      const parts = value.split(/e/i);
      if (parts.length > 2) throw new Error('Invalid integer: ' + value);
      if (parts.length === 2) {
        let exp = +parts[1];
        if (exp !== Math.floor(exp) || !isSmall(exp)) throw new Error('Invalid integer: ' + value);
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
      for (let i = value.length; i > 0; i -= LOG_BASE) {
        digits.push(+value.substring(Math.max(0, i - LOG_BASE), i));
      }
      return new BigInteger(digits, sign);
    }
    throw new Error('Invalid value: ' + value);
  }

  function add(a, b) {
    const result = [];
    let carry = 0;
    const length = Math.max(a.length, b.length);
    for (let i = 0; i < length || carry; i++) {
      const sum = (a[i] || 0) + (b[i] || 0) + carry;
      result[i] = sum % BASE;
      carry = Math.floor(sum / BASE);
    }
    return result;
  }

  function subtract(a, b) {
    const result = [];
    let borrow = 0;
    for (let i = 0; i < a.length; i++) {
      const diff = (a[i] || 0) - (b[i] || 0) - borrow;
      if (diff < 0) {
        result[i] = diff + BASE;
        borrow = 1;
      } else {
        result[i] = diff;
        borrow = 0;
      }
    }
    trim(result);
    return result;
  }

  function multiply(a, b) {
    const result = Array(a.length + b.length).fill(0);
    for (let i = 0; i < a.length; i++) {
      let carry = 0;
      for (let j = 0; j < b.length || carry; j++) {
        const product = result[i + j] + a[i] * (b[j] || 0) + carry;
        result[i + j] = product % BASE;
        carry = Math.floor(product / BASE);
      }
    }
    trim(result);
    return result;
  }

  function trim(arr) {
    while (arr.length > 1 && arr[arr.length - 1] === 0) arr.pop();
  }

  function compare(a, b) {
    if (a.length !== b.length) return a.length > b.length ? 1 : -1;
    for (let i = a.length - 1; i >= 0; i--) {
      if (a[i] !== b[i]) return a[i] > b[i] ? 1 : -1;
    }
    return 0;
  }

  function divide(a, b) {
    const result = [];
    let remainder = [];
    for (let i = a.length - 1; i >= 0; i--) {
      remainder.unshift(a[i]);
      trim(remainder);
      let quotient = 0;
      while (compare(remainder, b) >= 0) {
        remainder = subtract(remainder, b);
        quotient++;
      }
      result[i] = quotient;
    }
    trim(result);
    return [result, remainder];
  }

  function BigInt(value) {
    return parseValue(value);
  }

  BigInt.prototype.add = function (v) {
    const n = parseValue(v);
    if (this.sign !== n.sign) return this.subtract(n.negate());
    const result = this.isSmall && n.isSmall
      ? new SmallInteger(this.value + n.value)
      : new BigInteger(add(this.value, n.value), this.sign);
    return result;
  };

  BigInt.prototype.subtract = function (v) {
    const n = parseValue(v);
    if (this.sign !== n.sign) return this.add(n.negate());
    const cmp = compare(this.value, n.value);
    if (cmp === 0) return BigInt(0);
    const result = cmp > 0
      ? new BigInteger(subtract(this.value, n.value), this.sign)
      : new BigInteger(subtract(n.value, this.value), !this.sign);
    return result;
  };

  BigInt.prototype.multiply = function (v) {
    const n = parseValue(v);
    const result = this.isSmall && n.isSmall
      ? new SmallInteger(this.value * n.value)
      : new BigInteger(multiply(this.value, n.value), this.sign !== n.sign);
    return result;
  };

  BigInt.prototype.divide = function (v) {
    const n = parseValue(v);
    if (n.isZero()) throw new Error('Division by zero');
    const [quotient] = divide(this.value, n.value);
    return new BigInteger(quotient, this.sign !== n.sign);
  };

  BigInt.prototype.mod = function (v) {
    const n = parseValue(v);
    if (n.isZero()) throw new Error('Division by zero');
    const [, remainder] = divide(this.value, n.value);
    return new BigInteger(remainder, this.sign);
  };

  return BigInt;
})();