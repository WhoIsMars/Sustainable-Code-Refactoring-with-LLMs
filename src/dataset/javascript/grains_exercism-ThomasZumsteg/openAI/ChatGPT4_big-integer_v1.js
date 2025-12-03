var bigInt = (function () {
  'use strict';

  const BASE = 1e7;
  const LOG_BASE = 7;
  const MAX_INT = 9007199254740992;
  const MAX_INT_ARR = [MAX_INT];
  const MAX_INT_LOG = Math.log(MAX_INT);

  class BigInt {
    constructor(value, sign) {
      this.value = value;
      this.sign = sign;
      this.isSmall = false;
    }
  }

  class SmallInt {
    constructor(value) {
      this.value = value;
      this.sign = value < 0;
      this.isSmall = true;
    }
  }

  function isSmall(value) {
    return -MAX_INT < value && value < MAX_INT;
  }

  function toArray(value) {
    if (value < BASE) return [value];
    if (value < BASE * BASE) return [value % BASE, Math.floor(value / BASE)];
    return [value % BASE, Math.floor(value / BASE) % BASE, Math.floor(value / (BASE * BASE))];
  }

  function trim(arr) {
    while (arr.length > 1 && arr[arr.length - 1] === 0) arr.pop();
  }

  function addArrays(a, b) {
    const length = Math.max(a.length, b.length);
    const result = new Array(length);
    let carry = 0;

    for (let i = 0; i < length; i++) {
      const sum = (a[i] || 0) + (b[i] || 0) + carry;
      carry = Math.floor(sum / BASE);
      result[i] = sum % BASE;
    }

    if (carry > 0) result.push(carry);
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

    trim(result);
    return result;
  }

  function multiplyArrays(a, b) {
    const result = new Array(a.length + b.length).fill(0);

    for (let i = 0; i < a.length; i++) {
      let carry = 0;
      for (let j = 0; j < b.length || carry > 0; j++) {
        const product = result[i + j] + a[i] * (b[j] || 0) + carry;
        carry = Math.floor(product / BASE);
        result[i + j] = product % BASE;
      }
    }

    trim(result);
    return result;
  }

  function divideArrays(a, b) {
    const result = [];
    let remainder = [];

    for (let i = a.length - 1; i >= 0; i--) {
      remainder.unshift(a[i]);
      trim(remainder);

      let quotient = 0;
      while (compareArrays(remainder, b) >= 0) {
        remainder = subtractArrays(remainder, b);
        quotient++;
      }

      result.unshift(quotient);
    }

    trim(result);
    return [result, remainder];
  }

  function compareArrays(a, b) {
    if (a.length !== b.length) return a.length > b.length ? 1 : -1;
    for (let i = a.length - 1; i >= 0; i--) {
      if (a[i] !== b[i]) return a[i] > b[i] ? 1 : -1;
    }
    return 0;
  }

  function parseValue(value) {
    if (value instanceof BigInt || value instanceof SmallInt) return value;
    if (typeof value === 'number') {
      if (isSmall(value)) return new SmallInt(value);
      return new BigInt(toArray(value), value < 0);
    }
    if (typeof value === 'string') {
      const sign = value[0] === '-';
      if (sign) value = value.slice(1);
      const arr = [];
      for (let i = value.length; i > 0; i -= LOG_BASE) {
        arr.push(+value.substring(Math.max(0, i - LOG_BASE), i));
      }
      return new BigInt(arr, sign);
    }
    throw new Error('Invalid value');
  }

  BigInt.prototype.add = function (other) {
    other = parseValue(other);
    if (this.sign !== other.sign) return this.subtract(other.negate());
    const result = addArrays(this.value, other.value);
    return new BigInt(result, this.sign);
  };

  SmallInt.prototype.add = function (other) {
    other = parseValue(other);
    if (this.sign !== other.sign) return this.subtract(other.negate());
    const result = this.value + other.value;
    return isSmall(result) ? new SmallInt(result) : new BigInt(toArray(result), this.sign);
  };

  BigInt.prototype.subtract = function (other) {
    other = parseValue(other);
    if (this.sign !== other.sign) return this.add(other.negate());
    const cmp = compareArrays(this.value, other.value);
    if (cmp === 0) return new SmallInt(0);
    const result = cmp > 0
      ? subtractArrays(this.value, other.value)
      : subtractArrays(other.value, this.value);
    return new BigInt(result, cmp < 0 ? !this.sign : this.sign);
  };

  SmallInt.prototype.subtract = function (other) {
    other = parseValue(other);
    if (this.sign !== other.sign) return this.add(other.negate());
    const result = this.value - other.value;
    return isSmall(result) ? new SmallInt(result) : new BigInt(toArray(result), this.sign);
  };

  BigInt.prototype.multiply = function (other) {
    other = parseValue(other);
    const result = multiplyArrays(this.value, other.value);
    return new BigInt(result, this.sign !== other.sign);
  };

  SmallInt.prototype.multiply = function (other) {
    other = parseValue(other);
    const result = this.value * other.value;
    return isSmall(result) ? new SmallInt(result) : new BigInt(toArray(result), this.sign !== other.sign);
  };

  BigInt.prototype.divide = function (other) {
    other = parseValue(other);
    const [quotient] = divideArrays(this.value, other.value);
    return new BigInt(quotient, this.sign !== other.sign);
  };

  SmallInt.prototype.divide = function (other) {
    other = parseValue(other);
    const result = Math.floor(this.value / other.value);
    return isSmall(result) ? new SmallInt(result) : new BigInt(toArray(result), this.sign !== other.sign);
  };

  return function (value) {
    return parseValue(value);
  };
})();