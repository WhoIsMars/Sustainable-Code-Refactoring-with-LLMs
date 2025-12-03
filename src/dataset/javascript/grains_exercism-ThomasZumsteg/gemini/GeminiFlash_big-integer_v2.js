var bigInt = function (e) {
  'use strict';

  const BASE = 1e7;
  const BASE_LOG = 7;
  const MAX_SAFE = 9007199254740992;
  const MAX_INT = Math.floor(MAX_SAFE);

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
    return -MAX_INT < num && num < MAX_INT;
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

  function fromBaseArray(arr) {
    const len = arr.length;
    if (len === 0) return 0;
    if (len < 4 && compareArrays(arr, BASE_ARRAY) < 0) {
      switch (len) {
        case 0:
          return 0;
        case 1:
          return arr[0];
        case 2:
          return arr[0] + arr[1] * BASE;
        default:
          return arr[0] + (arr[1] + arr[2] * BASE) * BASE;
      }
    }
    return arr;
  }

  function trim(arr) {
    let len = arr.length;
    while (len > 0 && arr[len - 1] === 0) {
      len--;
    }
    arr.length = len;
  }

  function createArray(size) {
    const arr = new Array(size);
    for (let i = 0; i < size; i++) {
      arr[i] = 0;
    }
    return arr;
  }

  function floor(num) {
    return num > 0 ? Math.floor(num) : Math.ceil(num);
  }

  function addArrays(arr1, arr2) {
    const len1 = arr1.length;
    const len2 = arr2.length;
    const result = new Array(len1);
    let carry = 0;
    let sum, i;

    for (i = 0; i < len2; i++) {
      sum = arr1[i] + arr2[i] + carry;
      carry = sum >= BASE ? 1 : 0;
      result[i] = sum - carry * BASE;
    }

    while (i < len1) {
      sum = arr1[i] + carry;
      carry = sum === BASE ? 1 : 0;
      result[i++] = sum - carry * BASE;
    }

    if (carry > 0) {
      result.push(carry);
    }

    return result;
  }

  function addArraysFaster(arr1, arr2) {
    return arr1.length >= arr2.length ? addArrays(arr1, arr2) : addArrays(arr2, arr1);
  }

  function subtractArrays(arr1, arr2) {
    const len1 = arr1.length;
    const len2 = arr2.length;
    const result = new Array(len1);
    let borrow = 0;
    let diff, i;

    for (i = 0; i < len2; i++) {
      diff = arr1[i] - borrow - arr2[i];
      borrow = diff < 0 ? 1 : 0;
      result[i] = diff + borrow * BASE;
    }

    for (i = len2; i < len1; i++) {
      diff = arr1[i] - borrow;
      if (diff < 0) {
        diff += BASE;
        borrow = 1;
      } else {
        borrow = 0;
      }
      result[i] = diff;
    }

    trim(result);
    return result;
  }

  function subtractArraysResultSign(arr1, arr2, negate) {
    let result;
    if (compareArrays(arr1, arr2) >= 0) {
      result = subtractArrays(arr1, arr2);
    } else {
      result = subtractArrays(arr2, arr1);
      negate = !negate;
    }
    result = fromBaseArray(result);
    return typeof result === 'number' ? (negate ? -result : result) : new BigInteger(result, negate);
  }

  function addSmall(arr, small, sign) {
    const len = arr.length;
    const result = new Array(len);
    let carry = -small;
    let sum, i;

    for (i = 0; i < len; i++) {
      sum = arr[i] + carry;
      carry = Math.floor(sum / BASE);
      result[i] = sum - carry * BASE;
      carry += 1;
    }

    while (carry > 0) {
      result[i++] = carry % BASE;
      carry = Math.floor(carry / BASE);
    }

    result = fromBaseArray(result);
    return typeof result === 'number' ? (sign ? -result : result) : new BigInteger(result, sign);
  }

  function multiplyArrays(arr1, arr2) {
    const len1 = arr1.length;
    const len2 = arr2.length;
    const size = len1 + len2;
    const result = createArray(size);
    let carry, product, i, j;

    for (i = 0; i < len1; ++i) {
      carry = 0;
      for (j = 0; j < len2; ++j) {
        product = arr1[i] * arr2[j] + result[i + j] + carry;
        carry = Math.floor(product / BASE);
        result[i + j] = product - carry * BASE;
      }
      result[i + j] += carry;
    }

    trim(result);
    return result;
  }

  function multiplySmall(arr, small) {
    const len = arr.length;
    const result = new Array(len);
    let carry = 0;
    let product, i;

    for (i = 0; i < len; i++) {
      product = arr[i] * small + carry;
      carry = Math.floor(product / BASE);
      result[i] = product - carry * BASE;
    }

    while (carry > 0) {
      result[i++] = carry % BASE;
      carry = Math.floor(carry / BASE);
    }

    return result;
  }

  function squareArray(arr) {
    const len = arr.length;
    const size = len + len;
    const result = createArray(size);
    let carry, product, i, j;

    for (i = 0; i < len; i++) {
      carry = 0;
      for (j = 0; j < len; j++) {
        product = arr[i] * arr[j] + result[i + j] + carry;
        carry = Math.floor(product / BASE);
        result[i + j] = product - carry * BASE;
      }
      result[i + j] += carry;
    }

    trim(result);
    return result;
  }

  function divModArrays(numerator, denominator) {
    const lenN = numerator.length;
    const lenD = denominator.length;
    const result = createArray(lenD);
    const base = BASE;
    const lastDenominator = denominator[lenD - 1];
    const factor = Math.ceil(base / (2 * lastDenominator));
    const numeratorScaled = multiplySmall(numerator, factor);
    const denominatorScaled = multiplySmall(denominator, factor);
    let n = numeratorScaled.length;
    let d = denominatorScaled.length;

    numeratorScaled.push(0);
    denominatorScaled.push(0);

    let q, r, t, i, j;
    for (i = n - d; i >= 0; i--) {
      q = Math.floor((numeratorScaled[i + d] * base + numeratorScaled[i + d - 1]) / denominatorScaled[d - 1]);
      r = 0;

      do {
        t = 0;
        for (j = 0; j < d; j++) {
          t += denominatorScaled[j] * q;
          numeratorScaled[i + j] -= t;
          t = Math.floor(t / base);
          if (numeratorScaled[i + j] < 0) {
            numeratorScaled[i + j] += base;
            t++;
          }
        }
        numeratorScaled[i + d] -= t;
        if (numeratorScaled[i + d] < 0) {
          q--;
          t = 0;
          for (j = 0; j < d; j++) {
            t = numeratorScaled[i + j] + denominatorScaled[j];
            numeratorScaled[i + j] = t % base;
            t = Math.floor(t / base);
          }
          numeratorScaled[i + d] += t;
        }
        r++;
      } while (r < 3);

      result[i] = q;
    }

    numeratorScaled.pop();
    denominatorScaled.pop();
    const remainder = divideBySmall(numeratorScaled, factor)[0];

    return [fromBaseArray(result), remainder];
  }

  function divideBySmall(arr, small) {
    const len = arr.length;
    const result = createArray(len);
    let carry = 0;
    let quotient, i;

    for (i = len - 1; i >= 0; --i) {
      quotient = carry * BASE + arr[i];
      result[i] = Math.floor(quotient / small);
      carry = quotient % small;
    }

    return [result, carry | 0];
  }

  function shiftLeftArray(arr, places) {
    const result = [];
    while (places-- > 0) {
      result.push(0);
    }
    return result.concat(arr);
  }

  function karatsubaMultiply(arr1, arr2) {
    const len = Math.max(arr1.length, arr2.length);
    if (len <= 400) {
      return multiplyArrays(arr1, arr2);
    }

    const half = Math.ceil(len / 2);
    const low1 = arr1.slice(0, half);
    const high1 = arr1.slice(half);
    const low2 = arr2.slice(0, half);
    const high2 = arr2.slice(half);

    const z0 = karatsubaMultiply(low1, low2);
    const z1 = karatsubaMultiply(addArraysFaster(low1, high1), addArraysFaster(low2, high2));
    const z2 = karatsubaMultiply(high1, high2);

    const result = addArraysFaster(addArraysFaster(z0, shiftLeftArray(subtractArrays(subtractArrays(z1, z0), z2), half)), shiftLeftArray(z2, 2 * half));
    return result;
  }

  function compareArrays(arr1, arr2) {
    if (arr1.length !== arr2.length) {
      return arr1.length > arr2.length ? 1 : -1;
    }
    for (let i = arr1.length - 1; i >= 0; i--) {
      if (arr1[i] !== arr2[i]) {
        return arr1[i] > arr2[i] ? 1 : -1;
      }
    }
    return 0;
  }

  function toBaseString(big, base) {
    base = bigInt(base);
    if (base.isZero()) {
      if (big.isZero()) return '0';
      throw new Error('Cannot convert nonzero numbers to base 0.');
    }
    if (base.equals(-1)) {
      return big.isZero() ? '0' : big.isNegative() ? new Array(1 - big).join('10') : '1' + new Array(+big).join('01');
    }

    let result = '';
    const isNegative = big.isNegative() && base.isPositive();
    if (isNegative) {
      result = '-';
      big = big.abs();
    }
    if (base.equals(1)) {
      return big.isZero() ? '0' : result + new Array(+big + 1).join('1');
    }

    const digits = [];
    let i = big;
    let divmod;
    while (i.isNegative() || i.compareAbs(base) >= 0) {
      divmod = i.divmod(base);
      i = divmod.quotient;
      const remainder = divmod.remainder;
      digits.push(toDigit(remainder));
    }
    digits.push(toDigit(i));

    return result + digits.reverse().join('');
  }

  function toDigit(num) {
    const value = num.value;
    return typeof value === 'number' && value <= 36 ? '0123456789abcdefghijklmnopqrstuvwxyz'.charAt(value) : '<' + value + '>';
  }

  function parseString(str, base) {
    if (typeof base === 'undefined') {
      base = 10;
    }
    if (+base === 10) {
      return bigInt(str);
    }

    base = bigInt(base);
    if (base.isZero()) {
      throw new Error('Cannot convert to base 0.');
    }

    let result = ZERO;
    let multiplier = ONE;
    const isNegative = str[0] === '-';
    for (let i = isNegative ? 1 : 0; i < str.length; i++) {
      const digit = str[i].toLowerCase();
      let num;
      const charCode = digit.charCodeAt(0);
      if (charCode >= 48 && charCode <= 57) {
        num = bigInt(digit);
      } else if (charCode >= 97 && charCode <= 122) {
        num = bigInt(digit.charCodeAt(0) - 87);
      } else {
        if (digit !== '<') throw new Error(digit + ' is not a valid character');
        let end = i;
        do {
          end++;
        } while (str[end] !== '>');
        num = bigInt(str.slice(i + 1, end));
      }
      result = result.add(num.times(multiplier));
      multiplier = multiplier.times(base);
    }
    return isNegative ? result.negate() : result;
  }

  function valueOf(big) {
    return +big.toString();
  }

  BigInteger.prototype.add = function (num) {
    const n = bigInt(num);
    if (this.sign !== n.sign) {
      return this.subtract(n.negate());
    }
    const a = this.value;
    const b = n.value;
    return n.isSmall ? new BigInteger(addSmall(a, Math.abs(b), this.sign), this.sign) : new BigInteger(addArrays(a, b), this.sign);
  };
  BigInteger.prototype.plus = BigInteger.prototype.add;

  SmallInteger.prototype.add = function (num) {
    const n = bigInt(num);
    const a = this.value;
    if (a < 0 !== n.sign) {
      return this.subtract(n.negate());
    }
    const b = n.value;
    if (n.isSmall) {
      if (isSmall(a + b)) return new SmallInteger(a + b);
      const baseArray = toBaseArray(Math.abs(b));
      return new BigInteger(addSmall(baseArray, Math.abs(a), a < 0), a < 0);
    }
    return new BigInteger(addSmall(b, Math.abs(a), a < 0), a < 0);
  };
  SmallInteger.prototype.plus = SmallInteger.prototype.add;

  BigInteger.prototype.subtract = function (num) {
    const n = bigInt(num);
    if (this.sign !== n.sign) {
      return this.add(n.negate());
    }
    const a = this.value;
    const b = n.value;
    return n.isSmall ? addSmall(a, Math.abs(b), !this.sign) : subtractArraysResultSign(a, b, this.sign);
  };
  BigInteger.prototype.minus = BigInteger.prototype.subtract;

  SmallInteger.prototype.subtract = function (num) {
    const n = bigInt(num);
    const a = this.value;
    if (a < 0 !== n.sign) {
      return this.add(n.negate());
    }
    const b = n.value;
    return n.isSmall ? new SmallInteger(a - b) : addSmall(b, Math.abs(a), a >= 0);
  };
  SmallInteger.prototype.minus = SmallInteger.prototype.subtract;

  BigInteger.prototype.negate = function () {
    return new BigInteger(this.value, !this.sign);
  };
  SmallInteger.prototype.negate = function () {
    const sign = this.sign;
    const num = new SmallInteger(-this.value);
    num.sign = !sign;
    return num;
  };

  BigInteger.prototype.abs = function () {
    return new BigInteger(this.value, false);
  };
  SmallInteger.prototype.abs = function () {
    return new SmallInteger(Math.abs(this.value));
  };

  BigInteger.prototype.multiply = function (num) {
    const n = bigInt(num);
    const a = this.value;
    const b = n.value;
    const sign = this.sign !== n.sign;

    if (n.isSmall) {
      if (b === 0) return ZERO;
      if (b === 1) return this;
      if (b === -1) return this.negate();
      const absB = Math.abs(b);
      if (absB < BASE) return new BigInteger(multiplySmall(a, absB), sign);
      const baseArray = toBaseArray(absB);
      return new BigInteger(multiplyArrays(a, baseArray), sign);
    }

    return a.length + b.length > 4000 ? new BigInteger(karatsubaMultiply(a, b), sign) : new BigInteger(multiplyArrays(a, b), sign);
  };
  BigInteger.prototype.times = BigInteger.prototype.multiply;

  SmallInteger.prototype.multiply = function (num) {
    const n = bigInt(num);
    const a = this.value;
    const b = n.value;
    if (a === 0) return ZERO;
    if (a === 1) return n;
    if (a === -1) return n.negate();

    if (n.isSmall) {
      if (isSmall(a * b)) return new SmallInteger(a * b);
      const baseArray = toBaseArray(Math.abs(b));
      return new BigInteger(multiplySmall(baseArray, Math.abs(a)), this.sign !== n.sign);
    }

    const absA = Math.abs(a);
    return absA < BASE ? new BigInteger(multiplySmall(b, absA), this.sign !== n.sign) : new BigInteger(multiplyArrays(b, toBaseArray(absA)), this.sign !== n.sign);
  };
  SmallInteger.prototype.times = SmallInteger.prototype.multiply;

  BigInteger.prototype.square = function () {
    return new BigInteger(squareArray(this.value), false);
  };
  SmallInteger.prototype.square = function () {
    const value = this.value * this.value;
    return isSmall(value) ? new SmallInteger(value) : new BigInteger(squareArray(toBaseArray(Math.abs(this.value))), false);
  };

  BigInteger.prototype.divmod = function (num) {
    const n = bigInt(num);
    return divModArraysFunc(this, n);
  };
  SmallInteger.prototype.divmod = BigInteger.prototype.divmod;

  BigInteger.prototype.divide = function (num) {
    return divModArraysFunc(this, num)[0];
  };
  SmallInteger.prototype.over = SmallInteger.prototype.divide = BigInteger.prototype.over = BigInteger.prototype.divide;

  BigInteger.prototype.mod = function (num) {
    return divModArraysFunc(this, num)[1];
  };
  SmallInteger.prototype.remainder = SmallInteger.prototype.mod = BigInteger.prototype.remainder = BigInteger.prototype.mod;

  BigInteger.prototype.pow = function (num) {
    const n = bigInt(num);
    const a = this.value;
    const b = n.value;
    let i, s, o;

    if (b === 0) return ONE;
    if (a === 0) return ZERO;
    if (a === 1) return ONE;
    if (a === -1) return n.isEven() ? ONE : MINUS_ONE;
    if (n.sign) return ZERO;
    if (!n.isSmall) throw new Error('The exponent ' + n.toString() + ' is too large.');

    if (this.isSmall && isSmall(i = Math.pow(a, b))) return new SmallInteger(floor(i));

    s = this;
    o = ONE;
    for (;;) {
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
    exponent = bigInt(exponent);
    modulus = bigInt(modulus);
    if (modulus.isZero()) throw new Error('Cannot take modPow with modulus 0');
    let result = ONE;
    let base = this.mod(modulus);
    if (base.isZero()) return ZERO;
    while (exponent.isPositive()) {
      if (exponent.isOdd()) result = result.multiply(base).mod(modulus);
      exponent = exponent.divide(2);
      base = base.square().mod(modulus);
    }
    return result;
  };
  SmallInteger.prototype.modPow = BigInteger.prototype.modPow;

  BigInteger.prototype.compareAbs = function (num) {
    const n = bigInt(num);
    const a = this.value;
    const b = n.value;
    return n.isSmall ? 1 : compareArrays(a, b);
  };
  SmallInteger.prototype.compareAbs = function (num) {
    const n = bigInt(num);
    const a = Math.abs(this.value);
    const b = n.value;
    return n.isSmall ? (b = Math.abs(b), a === b ? 0 : a > b ? 1 : -1) : -1;
  };

  BigInteger.prototype.compare = function (num) {
    const n = bigInt(num);
    const a = this.value;
    const b = n.value;
    if (this.sign !== n.sign) {
      return n.sign ? 1 : -1;
    }
    return n.isSmall ? (this.sign ? -1 : 1) : compareArrays(a, b) * (this.sign ? -1 : 1);
  };
  BigInteger.prototype.compareTo = BigInteger.prototype.compare;

  SmallInteger.prototype.compare = function (num) {
    const n = bigInt(num);
    const a = this.value;
    const b = n.value;
    return n.isSmall ? (a === b ? 0 : a > b ? 1 : -1) : a < 0 !== n.sign ? (a < 0 ? -1 : 1) : a < 0 ? 1 : -1;
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
    const n = bigInt(num);
    const b = n.value;
    return b === 0 ? false : b === 1 ? true : b === 2 ? this.isEven() : this.mod(n).equals(ZERO);
  };
  SmallInteger.prototype.isDivisibleBy = BigInteger.prototype.isDivisibleBy;

  BigInteger.prototype.isPrime = function () {
    const num = this.abs();
    const numMinusOne = num.prev();
    if (num.isUnit()) return false;
    if (num.equals(2) || num.equals(3) || num.equals(5)) return true;
    if (num.isEven() || num.isDivisibleBy(3) || num.isDivisibleBy(5)) return false;
    if (num.lesser(25)) return true;

    const primes = [2, 3, 5, 7, 11, 13, 17, 19];
    let r = numMinusOne;
    let i, s, o, u;
    while (r.isEven()) r = r.divide(2);
    for (o = 0; o < primes.length; o++) {
      u = bigInt(primes[o]).modPow(r, num);
      if (u.equals(ONE) || u.equals(numMinusOne)) continue;
      for (s = true, i = r; s && i.lesser(numMinusOne); i = i.multiply(2)) {
        u = u.square().mod(num);
        if (u.equals(numMinusOne)) s = false;
      }
      if (s) return false;
    }
    return true;
  };
  SmallInteger.prototype.isPrime = BigInteger.prototype.isPrime;

  BigInteger.prototype.next = function () {
    const value = this.value;
    return this.sign ? addSmall(value, 1, this.sign) : new BigInteger(addSmall(value, -1, this.sign), this.sign);
  };
  SmallInteger.prototype.next = function () {
    const value = this.value;
    return value + 1 < MAX_INT ? new SmallInteger(value + 1) : new BigInteger(BASE_ARRAY, false);
  };

  BigInteger.prototype.prev = function () {
    const value = this.value;
    return this.sign ? new BigInteger(addSmall(value, -1, true), true) : addSmall(value, 1, this.sign);
  };
  SmallInteger.prototype.prev = function () {
    const value = this.value;
    return value - 1 > -MAX_INT ? new SmallInteger(value - 1) : new BigInteger(BASE_ARRAY, true);
  };

  const POWERS_OF_TWO = [1];
  while (POWERS_OF_TWO[POWERS_OF_TWO.length - 1] <= BASE) {
    POWERS_OF_TWO.push(2 * POWERS_OF_TWO[POWERS_OF_TWO.length - 1]);
  }
  const BIT_COUNT = POWERS_OF_TWO.length;
  const MAX_POWER_OF_TWO = POWERS_OF_TWO[BIT_COUNT - 1];

  BigInteger.prototype.shiftLeft = function (num) {
    if (!isBigInt(num)) {
      return num.isNegative() ? this.shiftRight(num.abs()) : this.times(TWO.pow(num));
    }
    num = +num;
    if (num < 0) return this.shiftRight(-num);
    let big = this;
    while (num >= BIT_COUNT) {
      big = big.multiply(MAX_POWER_OF_TWO);
      num -= BIT_COUNT - 1;
    }
    return big.multiply(POWERS_OF_TWO[num]);
  };
  SmallInteger.prototype.shiftLeft = BigInteger.prototype.shiftLeft;

  BigInteger.prototype.shiftRight = function (num) {
    let divmod;
    if (!isBigInt(num)) {
      return num.isNegative() ? this.shiftLeft(num.abs()) : (divmod = this.divmod(TWO.pow(num)), divmod.remainder.isNegative() ? divmod.quotient.prev() : divmod.quotient);
    }
    num = +num;
    if (num < 0) return this.shiftLeft(-num);
    let big = this;
    while (num >= BIT_COUNT) {
      if (big.isZero()) return big;
      divmod = divModArraysFunc(big, MAX_POWER_OF_TWO);
      big = divmod[1].isNegative() ? divmod[0].prev() : divmod[0];
      num -= BIT_COUNT - 1;
    }
    divmod = divModArraysFunc(big, POWERS_OF_TWO[num]);
    return divmod[1].isNegative() ? divmod[0].prev() : divmod[0];
  };
  SmallInteger.prototype.shiftRight = BigInteger.prototype.shiftRight;

  BigInteger.prototype.not = function () {
    return this.negate().prev();
  };
  SmallInteger.prototype.not = BigInteger.prototype