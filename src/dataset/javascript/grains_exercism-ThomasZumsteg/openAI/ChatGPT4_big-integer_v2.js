var bigInt = (function () {
  'use strict';

  const BASE = 1e7;
  const LOG_BASE = 7;
  const MAX_INT = 9007199254740992;
  const BASE_ARR = [1];
  while (BASE_ARR[BASE_ARR.length - 1] <= BASE) BASE_ARR.push(BASE_ARR[BASE_ARR.length - 1] * 2);

  class BigInt {
    constructor(value, sign) {
      this.value = value;
      this.sign = sign;
    }

    static fromNumber(n) {
      return new BigInt([Math.abs(n)], n < 0);
    }

    static fromArray(arr, sign) {
      return new BigInt(arr, sign);
    }

    static isSmall(n) {
      return -MAX_INT < n && n < MAX_INT;
    }

    static trim(arr) {
      while (arr.length > 1 && arr[arr.length - 1] === 0) arr.pop();
      return arr;
    }

    static addArrays(a, b) {
      const result = [];
      let carry = 0;
      const maxLength = Math.max(a.length, b.length);
      for (let i = 0; i < maxLength || carry; i++) {
        const sum = (a[i] || 0) + (b[i] || 0) + carry;
        result.push(sum % BASE);
        carry = Math.floor(sum / BASE);
      }
      return result;
    }

    static subtractArrays(a, b) {
      const result = [];
      let borrow = 0;
      for (let i = 0; i < a.length; i++) {
        const diff = a[i] - (b[i] || 0) - borrow;
        if (diff < 0) {
          result.push(diff + BASE);
          borrow = 1;
        } else {
          result.push(diff);
          borrow = 0;
        }
      }
      return BigInt.trim(result);
    }

    static multiplyArrays(a, b) {
      const result = Array(a.length + b.length).fill(0);
      for (let i = 0; i < a.length; i++) {
        let carry = 0;
        for (let j = 0; j < b.length || carry; j++) {
          const prod = result[i + j] + a[i] * (b[j] || 0) + carry;
          result[i + j] = prod % BASE;
          carry = Math.floor(prod / BASE);
        }
      }
      return BigInt.trim(result);
    }

    static compareArrays(a, b) {
      if (a.length !== b.length) return a.length > b.length ? 1 : -1;
      for (let i = a.length - 1; i >= 0; i--) {
        if (a[i] !== b[i]) return a[i] > b[i] ? 1 : -1;
      }
      return 0;
    }

    add(other) {
      const b = BigInt.from(other);
      if (this.sign !== b.sign) return this.subtract(b.negate());
      const result = BigInt.addArrays(this.value, b.value);
      return BigInt.fromArray(result, this.sign);
    }

    subtract(other) {
      const b = BigInt.from(other);
      if (this.sign !== b.sign) return this.add(b.negate());
      const cmp = BigInt.compareArrays(this.value, b.value);
      if (cmp === 0) return BigInt.ZERO;
      const result = cmp > 0
        ? BigInt.subtractArrays(this.value, b.value)
        : BigInt.subtractArrays(b.value, this.value);
      return BigInt.fromArray(result, cmp > 0 ? this.sign : !this.sign);
    }

    multiply(other) {
      const b = BigInt.from(other);
      const result = BigInt.multiplyArrays(this.value, b.value);
      return BigInt.fromArray(result, this.sign !== b.sign);
    }

    negate() {
      return BigInt.fromArray(this.value, !this.sign);
    }

    static from(value) {
      if (value instanceof BigInt) return value;
      if (typeof value === 'number') return BigInt.fromNumber(value);
      throw new Error('Invalid input');
    }

    toString() {
      const str = this.value.reverse().map((v, i) => (i ? String(v).padStart(LOG_BASE, '0') : v)).join('');
      return this.sign ? `-${str}` : str;
    }
  }

  BigInt.ZERO = BigInt.fromNumber(0);
  BigInt.ONE = BigInt.fromNumber(1);

  return BigInt;
})();