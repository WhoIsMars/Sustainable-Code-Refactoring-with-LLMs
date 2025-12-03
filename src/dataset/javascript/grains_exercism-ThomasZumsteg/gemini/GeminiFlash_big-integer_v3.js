var bigInt = (function () {
  'use strict';

  const BASE = 1e7;
  const BASE_LOG = 7;
  const MAX_SAFE = 9007199254740992;
  const MAX_SAFE_BASE = Math.floor(MAX_SAFE);

  function BigInteger(value, sign) {
    this.value = value;
    this.sign = sign;
    this.isSmall = false;
  }

  function SmallInteger(value) {
    this.value = value;
    this.sign = value < 0;
    this.isSmall = true;
  }

  function isSmall(num) {
    return -MAX_SAFE_BASE < num && num < MAX_SAFE_BASE;
  }

  function toBaseArray(number) {
    if (number < BASE) {
      return [number];
    }
    if (number < BASE * BASE) {
      return [number % BASE, Math.floor(number / BASE)];
    }
    return [number % BASE, Math.floor(number / BASE) % BASE, Math.floor(number / (BASE * BASE))];
  }

  function trim(arr) {
    let i = arr.length;
    while (i > 0 && arr[i - 1] === 0) {
      i--;
    }
    arr.length = i;
  }

  function createArray(size) {
    const arr = new Array(size);
    for (let i = 0; i < size; i++) {
      arr[i] = 0;
    }
    return arr;
  }

  function smallToArray(num) {
    return [num];
  }

  function arrayToSmall(arr) {
    const len = arr.length;
    if (len === 0) return 0;
    if (len < 4 && compareArrays(arr, i) < 0) {
      switch (len) {
        case 0: return 0;
        case 1: return arr[0];
        case 2: return arr[0] + arr[1] * BASE;
        default: return arr[0] + (arr[1] + arr[2] * BASE) * BASE;
      }
    }
    return arr;
  }

  function addArrays(a, b) {
    const lenA = a.length;
    const lenB = b.length;
    const result = new Array(Math.max(lenA, lenB));
    let carry = 0;
    for (let i = 0; i < result.length; i++) {
      const sum = (a[i] || 0) + (b[i] || 0) + carry;
      carry = sum >= BASE ? 1 : 0;
      result[i] = sum - carry * BASE;
    }
    if (carry) {
      result.push(carry);
    }
    return result;
  }

  function subtractArrays(a, b) {
    const lenA = a.length;
    const lenB = b.length;
    const result = new Array(lenA);
    let borrow = 0;
    for (let i = 0; i < lenA; i++) {
      const diff = a[i] - (b[i] || 0) - borrow;
      borrow = diff < 0 ? 1 : 0;
      result[i] = diff + borrow * BASE;
    }
    trim(result);
    return result;
  }

  function multiplyArray(arr, num) {
    const len = arr.length;
    const result = new Array(len);
    let carry = 0;
    for (let i = 0; i < len; i++) {
      const prod = arr[i] * num + carry;
      carry = Math.floor(prod / BASE);
      result[i] = prod - carry * BASE;
    }
    if (carry) {
      result.push(carry);
    }
    return result;
  }

  function divideArray(arr, num) {
    const len = arr.length;
    const result = createArray(len);
    let remainder = 0;
    for (let i = len - 1; i >= 0; i--) {
      const dividend = remainder * BASE + arr[i];
      const quotient = Math.floor(dividend / num);
      remainder = dividend - quotient * num;
      result[i] = quotient;
    }
    trim(result);
    return [result, remainder];
  }

  function multiplyArrays(a, b) {
    const lenA = a.length;
    const lenB = b.length;
    const resultLen = lenA + lenB;
    const result = createArray(resultLen);

    for (let i = 0; i < lenA; i++) {
      let carry = 0;
      for (let j = 0; j < lenB; j++) {
        const prod = a[i] * b[j] + result[i + j] + carry;
        carry = Math.floor(prod / BASE);
        result[i + j] = prod - carry * BASE;
      }
      result[i + lenB] += carry;
    }

    trim(result);
    return result;
  }

  function compareArrays(a, b) {
    const lenA = a.length;
    const lenB = b.length;
    if (lenA !== lenB) {
      return lenA > lenB ? 1 : -1;
    }
    for (let i = lenA - 1; i >= 0; i--) {
      if (a[i] !== b[i]) {
        return a[i] > b[i] ? 1 : -1;
      }
    }
    return 0;
  }

  function karatsubaMultiply(x, y) {
    const n = Math.max(x.length, y.length);
    if (n <= 400) return multiplyArrays(x, y);
    const half = Math.ceil(n / 2);
    const low1 = x.slice(0, half);
    const high1 = x.slice(half);
    const low2 = y.slice(0, half);
    const high2 = y.slice(half);

    const z0 = karatsubaMultiply(low1, low2);
    const z1 = karatsubaMultiply(addArrays(low1, high1), addArrays(low2, high2));
    const z2 = karatsubaMultiply(high1, high2);

    const part1 = z2;
    const part2 = subtractArrays(subtractArrays(z1, z2), z0);
    const part3 = z0;

    const result = addArrays(addArrays(part3, shiftLeft(part2, half)), shiftLeft(part1, 2 * half));
    return result;
  }

  function shiftLeft(arr, places) {
    const newArr = createArray(places);
    return newArr.concat(arr);
  }

  function squareArray(arr) {
    const len = arr.length;
    const resultLen = 2 * len;
    const result = createArray(resultLen);

    for (let i = 0; i < len; i++) {
      let carry = 0;
      for (let j = 0; j < len; j++) {
        const prod = arr[i] * arr[j] + result[i + j] + carry;
        carry = Math.floor(prod / BASE);
        result[i + j] = prod - carry * BASE;
      }
      result[i + len] += carry;
    }

    trim(result);
    return result;
  }

  function divModArrays(numerator, denominator) {
    let quotient;
    let remainder;

    if (numerator.length + denominator.length <= 200) {
      [quotient, remainder] = simpleDivMod(numerator, denominator);
    } else {
      [quotient, remainder] = recursiveDivMod(numerator, denominator);
    }

    return [arrayToSmall(quotient), arrayToSmall(remainder)];
  }

  function simpleDivMod(numerator, denominator) {
    const nLen = numerator.length;
    const dLen = denominator.length;
    const quotient = createArray(nLen);
    const remainder = [];

    for (let i = nLen - 1; i >= 0; i--) {
      remainder.unshift(numerator[i]);
      let q = 0;
      while (compareArrays(remainder, denominator) >= 0) {
        remainder = subtractArrays(remainder, denominator);
        q++;
      }
      quotient[i] = q;
    }

    return [quotient, remainder];
  }

  function recursiveDivMod(numerator, denominator) {
    const n = numerator.length;
    const m = denominator.length;
    const result = createArray(n - m + 1);
    let temp = [];

    for (let i = n - m; i >= 0; i--) {
      temp = numerator.slice(0, m + i);
      while (compareArrays(temp, shiftLeft(denominator, i)) >= 0) {
        result[i]++;
        temp = subtractArrays(temp, shiftLeft(denominator, i));
      }
    }

    return [result, temp];
  }

  function toBaseString(bigInt, base) {
    if (bigInt.isZero()) return '0';
    if (base === -1) {
      if (bigInt.isZero()) return '0';
      return bigInt.isNegative() ? (new Array(1 - bigInt)).join('10') : '1' + (new Array(+bigInt)).join('01');
    }

    let str = '';
    let num = bigInt.abs();
    while (num.compareAbs(base) >= 0) {
      const divmod = num.divmod(base);
      num = divmod.quotient;
      str = digitToChar(divmod.remainder.value) + str;
    }
    str = digitToChar(num.value) + str;
    return bigInt.isNegative() ? '-' + str : str;
  }

  function digitToChar(digit) {
    return '0123456789abcdefghijklmnopqrstuvwxyz'.charAt(digit);
  }

  function parseFromString(str, base) {
    let isNegative = str[0] === '-';
    if (isNegative) str = str.slice(1);

    let result = zero;
    let multiplier = one;

    for (let i = str.length - 1; i >= 0; i--) {
      const digit = charToDigit(str[i]);
      result = result.add(multiplier.multiply(digit));
      multiplier = multiplier.multiply(base);
    }

    return isNegative ? result.negate() : result;
  }

  function charToDigit(char) {
    const code = char.charCodeAt(0);
    if (code >= 48 && code <= 57) return code - 48;
    if (code >= 97 && code <= 122) return code - 87;
    throw new Error('Invalid character: ' + char);
  }

  function valueOf(bigInt) {
    return +bigInt.toString();
  }

  BigInteger.prototype.add = function (num) {
    const n = toBigInt(num);
    if (this.sign !== n.sign) return this.subtract(n.negate());
    const a = this.value;
    const b = n.value;
    return new BigInteger(addArrays(a, b), this.sign);
  };
  BigInteger.prototype.plus = BigInteger.prototype.add;

  SmallInteger.prototype.add = function (num) {
    const n = toBigInt(num);
    const a = this.value;
    if (a < 0 !== n.sign) return this.subtract(n.negate());
    const b = n.value;
    if (n.isSmall) {
      if (isSmall(a + n.value)) return new SmallInteger(a + n.value);
      return new BigInteger(toBaseArray(Math.abs(a + n.value)), a < 0);
    }
    return new BigInteger(addArrays(b, toBaseArray(Math.abs(a))), a < 0);
  };
  SmallInteger.prototype.plus = SmallInteger.prototype.add;

  BigInteger.prototype.subtract = function (num) {
    const n = toBigInt(num);
    if (this.sign !== n.sign) return this.add(n.negate());
    const a = this.value;
    const b = n.value;
    const cmp = compareArrays(a, b);
    if (cmp === 0) return zero;
    const sign = cmp > 0 ? this.sign : !this.sign;
    const result = cmp > 0 ? subtractArrays(a, b) : subtractArrays(b, a);
    return new BigInteger(result, sign);
  };
  BigInteger.prototype.minus = BigInteger.prototype.subtract;

  SmallInteger.prototype.subtract = function (num) {
    const n = toBigInt(num);
    const a = this.value;
    if (a < 0 !== n.sign) return this.add(n.negate());
    const b = n.value;
    if (n.isSmall) {
      if (isSmall(a - n.value)) return new SmallInteger(a - n.value);
      return new BigInteger(toBaseArray(Math.abs(a - n.value)), a < 0);
    }
    const result = subtractArrays(b, toBaseArray(Math.abs(a)));
    return new BigInteger(result, a >= 0);
  };
  SmallInteger.prototype.minus = SmallInteger.prototype.subtract;

  BigInteger.prototype.negate = function () {
    return new BigInteger(this.value, !this.sign);
  };

  SmallInteger.prototype.negate = function () {
    return new SmallInteger(-this.value);
  };

  BigInteger.prototype.abs = function () {
    return new BigInteger(this.value, false);
  };

  SmallInteger.prototype.abs = function () {
    return new SmallInteger(Math.abs(this.value));
  };

  BigInteger.prototype.multiply = function (num) {
    const n = toBigInt(num);
    if (n.isZero()) return zero;
    if (n.isOne()) return this;
    if (n.isMinusOne()) return this.negate();

    const a = this.value;
    const b = n.value;
    const sign = this.sign !== n.sign;

    if (n.isSmall) {
      const absValue = Math.abs(n.value);
      if (absValue < BASE) return new BigInteger(multiplyArray(a, absValue), sign);
    }

    if (a.length + b.length > 4000) {
      return new BigInteger(karatsubaMultiply(a, b), sign);
    } else {
      return new BigInteger(multiplyArrays(a, b), sign);
    }
  };
  BigInteger.prototype.times = BigInteger.prototype.multiply;

  SmallInteger.prototype.multiply = function (num) {
    const n = toBigInt(num);
    if (n.isZero()) return zero;
    if (n.isOne()) return this;
    if (n.isMinusOne()) return this.negate();

    const a = this.value;
    const b = n.value;
    const sign = a < 0 !== n.sign;

    if (n.isSmall) {
      if (isSmall(a * n.value)) return new SmallInteger(a * n.value);
      return new BigInteger(toBaseArray(Math.abs(a * n.value)), sign);
    }

    const absValue = Math.abs(a);
    if (absValue < BASE) return new BigInteger(multiplyArray(b, absValue), sign);
    return new BigInteger(multiplyArrays(b, toBaseArray(absValue)), sign);
  };
  SmallInteger.prototype.times = SmallInteger.prototype.multiply;

  BigInteger.prototype.square = function () {
    return new BigInteger(squareArray(this.value), false);
  };

  SmallInteger.prototype.square = function () {
    const value = this.value * this.value;
    if (isSmall(value)) return new SmallInteger(value);
    return new BigInteger(squareArray(toBaseArray(Math.abs(this.value))), false);
  };

  BigInteger.prototype.divmod = function (num) {
    const n = toBigInt(num);
    const a = this;
    const b = n;

    const aAbs = a.abs();
    const bAbs = b.abs();

    if (bAbs.isZero()) throw new Error('Cannot divide by zero');
    if (aAbs.compareAbs(bAbs) < 0) return { quotient: zero, remainder: a };
    if (aAbs.equals(bAbs)) return { quotient: new SmallInteger(a.sign === b.sign ? 1 : -1), remainder: zero };

    let quotient, remainder;
    if (b.isSmall) {
      const bValue = Math.abs(b.value);
      [quotient, remainder] = divideArray(a.value, bValue);
      quotient = arrayToSmall(quotient);
      remainder = new SmallInteger(remainder);
    } else {
      [quotient, remainder] = divModArrays(a.value, b.value);
    }

    const qSign = a.sign !== b.sign;
    const q = typeof quotient === 'number' ? new SmallInteger(qSign ? -quotient : quotient) : new BigInteger(quotient, qSign);
    const r = typeof remainder === 'number' ? new SmallInteger(a.sign ? -remainder : remainder) : new BigInteger(remainder, a.sign);
    return { quotient: q, remainder: r };
  };

  SmallInteger.prototype.divmod = BigInteger.prototype.divmod;

  BigInteger.prototype.divide = function (num) {
    return this.divmod(num).quotient;
  };
  BigInteger.prototype.over = BigInteger.prototype.divide;

  SmallInteger.prototype.divide = BigInteger.prototype.divide;
  SmallInteger.prototype.over = SmallInteger.prototype.divide;

  BigInteger.prototype.mod = function (num) {
    return this.divmod(num).remainder;
  };
  BigInteger.prototype.remainder = BigInteger.prototype.mod;

  SmallInteger.prototype.mod = BigInteger.prototype.mod;
  SmallInteger.prototype.remainder = SmallInteger.prototype.mod;

  BigInteger.prototype.pow = function (num) {
    const n = toBigInt(num);
    let a = this.value;
    let b = n.value;
    let i, s, o;

    if (b === 0) return one;
    if (a === 0) return zero;
    if (a === 1) return one;
    if (a === -1) return n.isEven() ? one : minusOne;
    if (n.sign) return zero;
    if (!n.isSmall) throw new Error('The exponent ' + n.toString() + ' is too large.');

    let result;
    if (this.isSmall && isSmall(i = Math.pow(a, b))) return new SmallInteger(i);

    s = this;
    o = one;

    for (; ;) {
      if (b & !0) {
        o = o.times(s);
        --b;
      }
      if (b === 0) break;
      b /= 2;
      s = s.square();
    }
    return o;
  };

  SmallInteger.prototype.pow = BigInteger.prototype.pow;

  BigInteger.prototype.modPow = function (exponent, modulus) {
    exponent = toBigInt(exponent);
    modulus = toBigInt(modulus);
    if (modulus.isZero()) throw new Error('Cannot take modPow with modulus 0');
    let result = one;
    let base = this.mod(modulus);
    if (base.isZero()) return zero;

    while (exponent.isPositive()) {
      if (exponent.isOdd()) result = result.multiply(base).mod(modulus);
      exponent = exponent.divide(2);
      base = base.square().mod(modulus);
    }
    return result;
  };

  SmallInteger.prototype.modPow = BigInteger.prototype.modPow;

  BigInteger.prototype.compareAbs = function (num) {
    const n = toBigInt(num);
    const a = this.value;
    const b = n.value;
    if (n.isSmall) return 1;
    return compareArrays(a, b);
  };

  SmallInteger.prototype.compareAbs = function (num) {
    const n = toBigInt(num);
    const a = Math.abs(this.value);
    const b = n.value;
    if (n.isSmall) {
      const bValue = Math.abs(n.value);
      return a === bValue ? 0 : a > bValue ? 1 : -1;
    }
    return -1;
  };

  BigInteger.prototype.compare = function (num) {
    const n = toBigInt(num);
    if (this.sign !== n.sign) return n.sign ? 1 : -1;
    if (n.isSmall) return this.sign ? -1 : 1;
    const cmp = compareArrays(this.value, n.value);
    return cmp * (this.sign ? -1 : 1);
  };
  BigInteger.prototype.compareTo = BigInteger.prototype.compare;

  SmallInteger.prototype.compare = function (num) {
    const n = toBigInt(num);
    const a = this.value;
    const b = n.value;
    if (n.isSmall) return a === n.value ? 0 : a > n.value ? 1 : -1;
    if (a < 0 !== n.sign) return a < 0 ? -1 : 1;
    return a < 0 ? 1 : -1;
  };
  SmallInteger.prototype.compareTo = SmallInteger.prototype.compare;

  BigInteger.prototype.equals = function (num) {
    return this.compare(num) === 0;
  };
  SmallInteger.prototype.eq = SmallInteger.prototype.equals = BigInteger.prototype.eq = BigInteger.prototype.equals;

  BigInteger.prototype.notEquals = function (num) {
    return this.compare(num) !== 0;
  };
  SmallInteger.prototype.neq = SmallInteger.prototype.notEquals = BigInteger.prototype.neq = BigInteger.prototype.notEquals;

  BigInteger.prototype.greater = function (num) {
    return this.compare(num) > 0;
  };
  SmallInteger.prototype.gt = SmallInteger.prototype.greater = BigInteger.prototype.gt = BigInteger.prototype.greater;

  BigInteger.prototype.lesser = function (num) {
    return this.compare(num) < 0;
  };
  SmallInteger.prototype.lt = SmallInteger.prototype.lesser = BigInteger.prototype.lt = BigInteger.prototype.lesser;

  BigInteger.prototype.greaterOrEquals = function (num) {
    return this.compare(num) >= 0;
  };
  SmallInteger.prototype.geq = SmallInteger.prototype.greaterOrEquals = BigInteger.prototype.geq = BigInteger.prototype.greaterOrEquals;

  BigInteger.prototype.lesserOrEquals = function (num) {
    return this.compare(num) <= 0;
  };
  SmallInteger.prototype.leq = SmallInteger.prototype.lesserOrEquals = BigInteger.prototype.leq = BigInteger.prototype.lesserOrEquals;

  BigInteger.prototype.isEven = function () {
    return (this.value[0] & 1) === 0;
  };
  SmallInteger.prototype.isEven = function () {
    return (this.value & 1) === 0;
  };

  BigInteger.prototype.isOdd = function () {
    return (this.value[0] & 1) === 1;
  };
  SmallInteger.prototype.isOdd = function () {
    return (this.value & 1) === 1;
  };

  BigInteger.prototype.isPositive = function () {
    return !this.sign;
  };
  SmallInteger.prototype.isPositive = function () {
    return this.value > 0;
  };

  BigInteger.prototype.isNegative = function () {
    return this.sign;
  };
  SmallInteger.prototype.isNegative = function () {
    return this.value < 0;
  };

  BigInteger.prototype.isUnit = function () {
    return false;
  };
  SmallInteger.prototype.isUnit = function () {
    return Math.abs(this.value) === 1;
  };

  BigInteger.prototype.isZero = function () {
    return false;
  };
  SmallInteger.prototype.isZero = function () {
    return this.value === 0;
  };

  BigInteger.prototype.isDivisibleBy = function (num) {
    const n = toBigInt(num);
    const nValue = n.value;
    if (nValue === 0) return false;
    if (nValue === 1) return true;
    if (nValue === 2) return this.isEven();
    return this.mod(n).equals(zero);
  };
  SmallInteger.prototype.isDivisibleBy = BigInteger.prototype.isDivisibleBy;

  BigInteger.prototype.isPrime = function () {
    const abs = this.abs();
    const prev = abs.prev();
    if (abs.isUnit()) return false;
    if (abs.equals(2) || abs.equals(3) || abs.equals(5)) return true;
    if (abs.isEven() || abs.isDivisibleBy(3) || abs.isDivisibleBy(5)) return false;
    if (abs.lesser(25)) return true;

    const primes = [2, 3, 5, 7, 11, 13, 17, 19];
    let r = prev;
    while (r.isEven()) r = r.divide(2);

    for (let i = 0; i < primes.length; i++) {
      let u = bigInt(primes[i]).modPow(r, abs);
      if (u.equals(one) || u.equals(prev)) continue;

      let s = true;
      for (let j = r; s && j.lesser(prev); j = j.multiply(2)) {
        u = u.square().mod(abs);
        if (u.equals(prev)) s = false;
      }
      if (s) return false;
    }
    return true;
  };
  SmallInteger.prototype.isPrime = BigInteger.prototype.isPrime;

  BigInteger.prototype.next = function () {
    if (this.sign) {
      return new BigInteger(subtractArrays(this.value, smallToArray(1)), this.sign);
    }
    return new BigInteger(addArrays(this.value, smallToArray(1)), this.sign);
  };

  SmallInteger.prototype.next = function () {
    const value = this.value;
    if (value + 1 < MAX_SAFE_BASE) return new SmallInteger(value + 1);
    return new BigInteger(i, false);
  };

  BigInteger.prototype.prev = function () {
    if (this.sign) {
      return new BigInteger(addArrays(this.value, smallToArray(1)), true);
    }
    return new BigInteger(subtractArrays(this.value, smallToArray(1)), this.sign);
  };

  SmallInteger.prototype.prev = function () {
    const value = this.value;
    if (value - 1 > -MAX_SAFE_BASE) return new SmallInteger(value - 1);
    return new BigInteger(i, true);
  };

  const powersOfTwo = [1];
  while (powersOfTwo[powersOfTwo.length - 1] <= BASE) powersOfTwo.push(2 * powersOfTwo[powersOfTwo.length - 1]);
  const powersOfTwoLength = powersOfTwo.length;
  const highestPowerOfTwo = powersOfTwo[powersOfTwoLength - 1];

  BigInteger.prototype.shiftLeft = function (num) {
    if (!isBigInt(num)) return num.isNegative() ? this.shiftRight(num.abs()) : this.times(two.pow(num));
    const n = +num;
    if (n < 0) return this.shiftRight(-n);

    let result = this;
    while (n >= powersOfTwoLength) {
      result = result.multiply(highestPowerOfTwo);
      n -= powersOfTwoLength - 1;
    }
    return result.multiply(powersOfTwo[n]);
  };
  SmallInteger.prototype.shiftLeft = BigInteger.prototype.shiftLeft;

  BigInteger.prototype.shiftRight = function (num) {
    let quotient;
    let remainder;
    if (!isBigInt(num)) return num.isNegative() ? this.shiftLeft(num.abs()) : (({ quotient, remainder } = this.divmod(two.pow(num))), remainder.isNegative() ? quotient.prev() : quotient);
    const n = +num;
    if (n < 0) return this.shiftLeft(-n);

    let result = this;
    while (n >= powersOfTwoLength) {
      if (result.isZero()) return result;
      ({ quotient, remainder } = result.divmod(highestPowerOfTwo));
      result = remainder.isNegative() ? quotient.prev() : quotient;
      n -= powersOfTwoLength - 1;
    }
    ({ quotient, remainder } = result.divmod(powersOfTwo[n]));
    return remainder.isNegative() ? quotient.prev() : quotient;
  };
  SmallInteger.prototype.shiftRight = BigInteger.prototype.shiftRight;

  BigInteger.prototype.not = function () {
    return this.negate().prev();
  };
  SmallInteger.prototype.not = BigInteger.prototype.not;

  BigInteger.prototype.and = function (num) {
    return bitwise(this, num, (a, b) => a & b);
  };
  SmallInteger.prototype.and = BigInteger.prototype.and;

  BigInteger.prototype.or = function (num) {
    return bitwise(this, num, (a, b) => a | b);
  };
  SmallInteger.prototype.or = BigInteger.prototype.or;

  BigInteger.prototype.xor = function (num) {
    return bitwise(this, num, (a, b) => a ^ b);
  };
  SmallInteger.prototype.xor = BigInteger.prototype.xor;

  function bitwise(x, y, op) {
    x = toBigInt(x);
    y = toBigInt(y);

    const xSign = x.isNegative();
    const ySign = y.isNegative();

    let xArr = xSign ? x.not() : x;
    let yArr = ySign ? y.not() : y;

    const result = [];
    let xBit, yBit;
    let i = 0;

    while (!xArr.isZero() || !yArr.isZero()) {
      xBit = xSign ? xArr.isEven() ? 1 : 0 : xArr.isEven() ? 0 : 1;
      yBit = ySign ? yArr.isEven() ? 1 : 0 : yArr.isEven() ? 0 : 1;

      result.push(op(xBit, yBit));
      xArr = xArr.over(2);
      yArr = yArr.over(2);
      i++;
    }

    let sum = bigInt(result.pop()).negate().times(bigInt(2).pow(result.length));
    while (result.length) sum = sum.add(bigInt(result.pop()).times(bigInt(2).pow(result.length)));
    return sum;
  }

  BigInteger.prototype.toString = function (base) {
    base = base || 10;
    if (base !== 10) return toBaseString(this, base);
    const value = this.value;
    let str = value[value.length - 1].toString();
    for (let i = value.length - 2; i >= 0; i--) {
      const part = value[i].toString();
      str += '0'.repeat(BASE_LOG - part.length) + part;
    }
    return this.sign ? '-' + str : str;
  };

  SmallInteger.prototype.toString = function