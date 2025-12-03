var bigInt = (function () {
  'use strict';

  const BASE = 1e7;
  const BASE_LOG = 7;
  const MAX_SAFE = 9007199254740992;
  const MAX_SAFE_BASE = 1e14;

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

  function isSafe(num) {
    return -MAX_SAFE < num && num < MAX_SAFE;
  }

  function toBaseArray(number) {
    if (number < BASE) {
      return [number];
    }
    if (number < MAX_SAFE_BASE) {
      return [number % BASE, Math.floor(number / BASE)];
    }
    return [number % BASE, Math.floor(number / BASE) % BASE, Math.floor(number / MAX_SAFE_BASE)];
  }

  function normalize(arr) {
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

  function fastAdd(x, y) {
    const xLen = x.length;
    const yLen = y.length;
    const result = new Array(xLen);
    let carry = 0;

    for (let i = 0; i < yLen; i++) {
      const sum = x[i] + y[i] + carry;
      carry = sum >= BASE ? 1 : 0;
      result[i] = sum - carry * BASE;
    }

    for (let i = yLen; i < xLen; i++) {
      const sum = x[i] + carry;
      carry = sum === BASE ? 1 : 0;
      result[i] = sum - carry * BASE;
    }

    if (carry > 0) {
      result.push(carry);
    }

    return result;
  }

  function add(x, y) {
    return x.length >= y.length ? fastAdd(x, y) : fastAdd(y, x);
  }

  function fastSubtract(x, y) {
    const xLen = x.length;
    const result = new Array(xLen);
    let borrow = 0;

    for (let i = 0; i < xLen; i++) {
      let diff = x[i] - borrow - (i < y.length ? y[i] : 0);
      if (diff < 0) {
        diff += BASE;
        borrow = 1;
      } else {
        borrow = 0;
      }
      result[i] = diff;
    }

    normalize(result);
    return result;
  }

  function subtract(x, y, negate) {
    let result = x.length >= y.length ? fastSubtract(x, y) : fastSubtract(y, x);
    if (x.length < y.length) {
      negate = !negate;
    }
    return { value: result, negate: negate };
  }

  function fastMultiply(x, digit) {
    const xLen = x.length;
    const result = new Array(xLen);
    let carry = 0;

    for (let i = 0; i < xLen; i++) {
      const product = x[i] * digit + carry;
      carry = Math.floor(product / BASE);
      result[i] = product - carry * BASE;
    }

    if (carry > 0) {
      result.push(carry);
    }

    return result;
  }

  function multiply(x, y) {
    const xLen = x.length;
    const yLen = y.length;
    const resultSize = xLen + yLen;
    const result = createArray(resultSize);

    for (let i = 0; i < xLen; i++) {
      let carry = 0;
      for (let j = 0; j < yLen; j++) {
        const product = x[i] * y[j] + result[i + j] + carry;
        carry = Math.floor(product / BASE);
        result[i + j] = product - carry * BASE;
      }
      result[i + yLen] += carry;
    }

    normalize(result);
    return result;
  }

  function divide(dividend, divisor) {
    if (divisor === 0) {
      throw new Error('Cannot divide by zero');
    }

    const dividendArr = Array.isArray(dividend) ? dividend : [dividend];
    const divisorArr = Array.isArray(divisor) ? divisor : [divisor];

    const dividendLen = dividendArr.length;
    const divisorLen = divisorArr.length;

    if (dividendLen < divisorLen) {
      return [[0], dividendArr];
    }

    if (dividendLen === divisorLen) {
      let i = dividendLen - 1;
      while (i >= 0 && dividendArr[i] === divisorArr[i]) {
        i--;
      }
      if (i < 0) {
        return [[1], [0]];
      }
      if (dividendArr[i] < divisorArr[i]) {
        return [[0], dividendArr];
      }
    }

    let quotient = createArray(dividendLen - divisorLen + 1);
    let remainder = dividendArr.slice();

    for (let i = dividendLen - divisorLen; i >= 0; i--) {
      let estimate = Math.floor((remainder[i + divisorLen] * BASE + remainder[i + divisorLen - 1]) / divisorArr[divisorLen - 1]);
      if (estimate >= BASE) {
        estimate = BASE - 1;
      }

      let temp = fastMultiply(divisorArr, estimate);
      while (compareArrays(remainder, i, temp) < 0) {
        estimate--;
        temp = fastMultiply(divisorArr, estimate);
      }

      quotient[i] = estimate;
      remainder = subtractInternal(remainder, temp, i);
    }

    normalize(quotient);
    normalize(remainder);

    return [quotient, remainder];
  }

  function subtractInternal(dividend, subtrahend, shift) {
    let borrow = 0;
    for (let i = 0; i < subtrahend.length; i++) {
      let diff = dividend[i + shift] - subtrahend[i] - borrow;
      if (diff < 0) {
        diff += BASE;
        borrow = 1;
      } else {
        borrow = 0;
      }
      dividend[i + shift] = diff;
    }
    return dividend;
  }

  function compareArrays(x, shift, y) {
    let i;
    for (i = x.length - 1; i >= shift + y.length; i--) {
      if (x[i] !== 0) return 1;
    }
    for (i = y.length - 1; i >= 0; i--) {
      let a = x[i + shift], b = y[i];
      if (a > b) return 1;
      if (a < b) return -1;
    }
    return 0;
  }

  function toString(bigInt, radix) {
    radix = bigInt(radix);
    if (radix.isZero()) {
      if (bigInt.isZero()) return '0';
      throw new Error('Cannot convert nonzero numbers to base 0.');
    }
    if (radix.equals(-1)) {
      return bigInt.isZero() ? '0' : bigInt.isNegative() ? (new Array(1 - bigInt)).join('10') : '1' + (new Array(+bigInt)).join('01');
    }

    let str = '';
    let isNegative = bigInt.isNegative();
    let num = isNegative ? bigInt.abs() : bigInt;

    if (radix.equals(1)) {
      return num.isZero() ? '0' : (isNegative ? '-' : '') + (new Array(+num + 1)).join('1');
    }

    let alphabet = '0123456789abcdefghijklmnopqrstuvwxyz';
    let base = radix.value;

    while (num.compareAbs(radix) >= 0) {
      let division = num.divmod(radix);
      num = division.quotient;
      let remainder = division.remainder;
      str = alphabet[remainder.abs().value] + str;
    }

    str = alphabet[num.abs().value] + str;
    return (isNegative ? '-' : '') + str;
  }

  function parseString(str, radix) {
    if (typeof str !== 'string') {
      str = String(str);
    }

    let isNegative = str[0] === '-';
    if (isNegative) {
      str = str.slice(1);
    }

    if (radix === undefined) {
      radix = 10;
    }

    if (radix !== 10) {
      return parseArbitraryBase(str, radix, isNegative);
    }

    if (!/^[0-9]+$/.test(str)) {
      throw new Error('Invalid integer: ' + str);
    }

    let parts = [];
    let len = str.length;
    let partLen = BASE_LOG;

    while (len > 0) {
      let part = str.substring(Math.max(0, len - partLen), len);
      parts.push(parseInt(part, 10));
      len -= partLen;
    }

    return new BigInteger(parts, isNegative);
  }

  function parseArbitraryBase(str, radix, isNegative) {
    let base = bigInt(radix);
    let result = bigInt(0);
    let multiplier = bigInt(1);

    for (let i = str.length - 1; i >= 0; i--) {
      let char = str[i].toLowerCase();
      let digit;

      if (char >= '0' && char <= '9') {
        digit = char.charCodeAt(0) - '0'.charCodeAt(0);
      } else if (char >= 'a' && char <= 'z') {
        digit = char.charCodeAt(0) - 'a'.charCodeAt(0) + 10;
      } else {
        throw new Error('Invalid character: ' + str[i]);
      }

      result = result.add(bigInt(digit).multiply(multiplier));
      multiplier = multiplier.multiply(base);
    }

    return isNegative ? result.negate() : result;
  }

  BigInteger.prototype.add = function (num) {
    let other = bigInt(num);
    if (this.sign !== other.sign) {
      return this.subtract(other.negate());
    }
    let x = this.value, y = other.value;
    return other.isSmall ? new BigInteger(fastAdd(x, Math.abs(y)), this.sign) : new BigInteger(add(x, y), this.sign);
  };
  BigInteger.prototype.plus = BigInteger.prototype.add;

  SmallInteger.prototype.add = function (num) {
    let other = bigInt(num);
    let n = this.value;
    if (n < 0 !== other.sign) {
      return this.subtract(other.negate());
    }
    let r = other.value;
    if (other.isSmall) {
      if (isSafe(n + r)) return new SmallInteger(n + r);
      r = toBaseArray(Math.abs(r));
    }
    return new BigInteger(fastAdd(r, Math.abs(n)), n < 0);
  };
  SmallInteger.prototype.plus = SmallInteger.prototype.add;

  BigInteger.prototype.subtract = function (num) {
    let other = bigInt(num);
    if (this.sign !== other.sign) {
      return this.add(other.negate());
    }
    let x = this.value, y = other.value;
    if (other.isSmall) {
      let result = subtract(x, Math.abs(y), this.sign);
      return typeof result.value === 'number' ? new SmallInteger(result.value) : new BigInteger(result.value, result.negate);
    } else {
      let result = subtract(x, y, this.sign);
      return typeof result.value === 'number' ? new SmallInteger(result.value) : new BigInteger(result.value, result.negate);
    }
  };
  BigInteger.prototype.minus = BigInteger.prototype.subtract;

  SmallInteger.prototype.subtract = function (num) {
    let other = bigInt(num);
    let n = this.value;
    if (n < 0 !== other.sign) {
      return this.add(other.negate());
    }
    let r = other.value;
    if (other.isSmall) {
      return new SmallInteger(n - r);
    } else {
      let result = subtract(r, Math.abs(n), n >= 0);
      return typeof result.value === 'number' ? new SmallInteger(result.value) : new BigInteger(result.value, result.negate);
    }
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
    let other = bigInt(num);
    let x = this.value, y = other.value;
    let negate = this.sign !== other.sign;

    if (other.isSmall) {
      if (y === 0) return ZERO;
      if (y === 1) return this;
      if (y === -1) return this.negate();
      let absY = Math.abs(y);
      if (absY < BASE) return new BigInteger(fastMultiply(x, absY), negate);
      y = toBaseArray(absY);
    }

    return x.length + y.length > 4000 ? new BigInteger(multiplyKaratsuba(x, y), negate) : new BigInteger(multiply(x, y), negate);
  };
  BigInteger.prototype.times = BigInteger.prototype.multiply;

  SmallInteger.prototype.multiply = function (num) {
    let other = bigInt(num);
    let r = this.value, i = other.value;

    if (r === 0) return ZERO;
    if (r === 1) return other;
    if (r === -1) return other.negate();

    if (other.isSmall) {
      if (isSafe(r * i)) return new SmallInteger(r * i);
      i = toBaseArray(Math.abs(i));
    }

    let negate = this.sign !== other.sign;
    let absR = Math.abs(r);
    return absR < BASE ? new BigInteger(fastMultiply(i, absR), negate) : new BigInteger(multiply(i, toBaseArray(absR)), negate);
  };
  SmallInteger.prototype.times = SmallInteger.prototype.multiply;

  BigInteger.prototype.square = function () {
    return new BigInteger(square(this.value), false);
  };

  SmallInteger.prototype.square = function () {
    let value = this.value * this.value;
    return isSafe(value) ? new SmallInteger(value) : new BigInteger(square(toBaseArray(Math.abs(this.value))), false);
  };

  BigInteger.prototype.divmod = function (num) {
    let denominator = bigInt(num);
    return divideBigInt(this, denominator);
  };

  SmallInteger.prototype.divmod = BigInteger.prototype.divmod;

  BigInteger.prototype.divide = function (num) {
    return divideBigInt(this, bigInt(num))[0];
  };

  SmallInteger.prototype.over = SmallInteger.prototype.divide = BigInteger.prototype.over = BigInteger.prototype.divide;

  BigInteger.prototype.mod = function (num) {
    return divideBigInt(this, bigInt(num))[1];
  };

  SmallInteger.prototype.remainder = SmallInteger.prototype.mod = BigInteger.prototype.remainder = BigInteger.prototype.mod;

  BigInteger.prototype.pow = function (num) {
    let exponent = bigInt(num);
    let base = this.value;
    let exp = exponent.value;

    if (exp === 0) return ONE;
    if (base === 0) return ZERO;
    if (base === 1) return ONE;
    if (base === -1) return exponent.isEven() ? ONE : MINUS_ONE;
    if (exponent.sign) return ZERO;
    if (!exponent.isSmall) throw new Error('The exponent ' + exponent.toString() + ' is too large.');

    let result, temp;
    if (this.isSmall && isSafe(result = Math.pow(base, exp))) return new SmallInteger(result);

    let isNegative = this.sign;
    let self = this.abs();
    result = ONE;

    while (true) {
      if (exp & 1) {
        result = result.multiply(self);
        --exp;
      }
      if (exp === 0) break;
      exp /= 2;
      self = self.square();
    }

    return isNegative && exponent.isOdd() ? result.negate() : result;
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
    let other = bigInt(num);
    let x = this.value, y = other.value;
    return other.isSmall ? 1 : compare(x, y);
  };

  SmallInteger.prototype.compareAbs = function (num) {
    let other = bigInt(num);
    let n = Math.abs(this.value), r = other.value;
    return other.isSmall ? (r = Math.abs(r), n === r ? 0 : n > r ? 1 : -1) : -1;
  };

  BigInteger.prototype.compare = function (num) {
    let other = bigInt(num);
    let x = this.value, y = other.value;
    if (this.sign !== other.sign) {
      return other.sign ? 1 : -1;
    }
    return other.isSmall ? this.sign ? -1 : 1 : compare(x, y) * (this.sign ? -1 : 1);
  };
  BigInteger.prototype.compareTo = BigInteger.prototype.compare;

  SmallInteger.prototype.compare = function (num) {
    let other = bigInt(num);
    let n = this.value, r = other.value;
    if (other.isSmall) {
      return n === r ? 0 : n > r ? 1 : -1;
    }
    return n < 0 !== other.sign ? (n < 0 ? -1 : 1) : (n < 0 ? 1 : -1);
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
    let divisor = bigInt(num);
    let n = divisor.value;
    return n === 0 ? false :
      n === 1 ? true :
        n === 2 ? this.isEven() :
          this.mod(divisor).equals(ZERO);
  };
  SmallInteger.prototype.isDivisibleBy = BigInteger.prototype.isDivisibleBy;

  BigInteger.prototype.isPrime = function () {
    let num = this.abs();
    let n = num.value;

    if (num.isUnit()) return false;
    if (num.equals(2) || num.equals(3) || num.equals(5)) return true;
    if (num.isEven() || num.isDivisibleBy(3) || num.isDivisibleBy(5)) return false;
    if (num.lesser(25)) return true;

    let arr = [2, 3, 5, 7, 11, 13, 17, 19];
    let t = num.prev();
    let r, i, s, o, u;

    while (t.isEven()) t = t.divide(2);

    for (o = 0; o < arr.length; o++) {
      u = bigInt(arr[o]).modPow(t, num);
      if (u.equals(ONE) || u.equals(num.prev())) continue;

      s = true;
      for (i = t; s && i.lesser(num.prev()); i = i.multiply(2)) {
        u = u.square().mod(num);
        if (u.equals(num.prev())) s = false;
      }
      if (s) return false;
    }

    return true;
  };
  SmallInteger.prototype.isPrime = BigInteger.prototype.isPrime;

  BigInteger.prototype.next = function () {
    let value = this.value;
    return this.sign ? new BigInteger(fastAdd(value, 1), this.sign) : new BigInteger(add(value, [1]), this.sign);
  };
  SmallInteger.prototype.next = function () {
    let value = this.value;
    return value + 1 < MAX_SAFE ? new SmallInteger(value + 1) : new BigInteger(toBaseArray(MAX_SAFE), false);
  };

  BigInteger.prototype.prev = function () {
    let value = this.value;
    return this.sign ? new BigInteger(fastAdd(value, 1), true) : new BigInteger(subtract(value, [1], this.sign).value, this.sign);
  };
  SmallInteger.prototype.prev = function () {
    let value = this.value;
    return value - 1 > -MAX_SAFE ? new SmallInteger(value - 1) : new BigInteger(toBaseArray(MAX_SAFE), true);
  };

  let powersOfTwo = [1];
  while (powersOfTwo[powersOfTwo.length - 1] <= BASE) powersOfTwo.push(2 * powersOfTwo[powersOfTwo.length - 1]);
  let powersOfTwoBitLength = powersOfTwo.length;
  let highestPowerOfTwo = powersOfTwo[powersOfTwoBitLength - 1];

  BigInteger.prototype.shiftLeft = function (num) {
    if (!isSmall(num)) return num.isNegative() ? this.shiftRight(num.abs()) : this.times(TWO.pow(num));
    num = +num;
    if (num < 0) return this.shiftRight(-num);
    let result = this;
    while (num >= powersOfTwoBitLength) {
      result = result.multiply(highestPowerOfTwo);
      num -= powersOfTwoBitLength - 1;
    }
    return result.multiply(powersOfTwo[num]);
  };
  SmallInteger.prototype.shiftLeft = BigInteger.prototype.shiftLeft;

  BigInteger.prototype.shiftRight = function (num) {
    let quotient;
    if (!isSmall(num)) return num.isNegative() ? this.shiftLeft(num.abs()) : (quotient = this.divmod(TWO.pow(num)), quotient[1].isNegative() ? quotient[0].prev() : quotient[0]);
    num = +num;
    if (num < 0) return this.shiftLeft(-num);
    let result = this;
    while (num >= powersOfTwoBitLength) {
      if (result.isZero()) return result;
      quotient = divideBigInt(result, highestPowerOfTwo);
      result = quotient[1].isNegative() ? quotient[0].prev() : quotient[0];
      num -= powersOfTwoBitLength - 1;
    }
    quotient = divideBigInt(result, powersOfTwo[num]);
    return quotient[1].isNegative() ? quotient[0].prev() : quotient[0];
  };
  SmallInteger.prototype.shiftRight = BigInteger.prototype.shiftRight;

  BigInteger.prototype.not = function () {
    return this.negate().prev();
  };
  SmallInteger.prototype.not = BigInteger.prototype.not;

  BigInteger.prototype.and = function (num) {
    return bitwise(this, bigInt(num), function (a, b) { return a & b; });
  };
  SmallInteger.prototype.and = BigInteger.prototype.and;

  BigInteger.prototype.or = function (num) {
    return bitwise(this, bigInt(num), function (a, b) { return a | b; });
  };
  SmallInteger.prototype.or = BigInteger.prototype.or;

  BigInteger.prototype.xor = function (num) {
    return bitwise(this, bigInt(num), function (a, b) { return a ^ b; });
  };
  SmallInteger.prototype.xor = BigInteger.prototype.xor;

  let bitwise = function (x, y, fn) {
    let xSign = x.isNegative(), ySign = y.isNegative();
    let xAbs = xSign ? x.not() : x, yAbs = ySign ? y.not() : y;
    let result = fn(xAbs, yAbs);
    if (xSign !== ySign) {
      if (!xSign) result = result.not();
    }
    return result;
  };

  function divideBigInt(num, den) {
    let numValue = num.value, numSign = num.sign;
    let denValue = den.value, denSign = den.sign;
    let quotient, remainder;

    if (denValue === 0) throw new Error('Cannot divide by zero');

    if (num.isSmall) {
      if (den.isSmall) {
        return [new SmallInteger(Math.floor(numValue / denValue)), new SmallInteger(numValue % denValue)];
      }
      numValue = toBaseArray(Math.abs(numValue));
    }
    if (den.isSmall) {
      if (denValue === 1) return [num, ZERO];
      if (denValue == -1) return [num.negate(), ZERO];
      let absDenValue = Math.abs(denValue);
      if (absDenValue < BASE) {
        let divmod = divmodSmall(numValue, absDenValue);
        quotient = divmod[0];
        remainder = divmod[1];
        return [new BigInteger(quotient, numSign !== denSign), new SmallInteger(remainder * (numSign ? -1 : 1))];
      }
      denValue = toBaseArray(absDenValue);
    }

    let divmod = divide(numValue, denValue);
    quotient = divmod[0];
    remainder = divmod[1];
    return [new BigInteger(quotient, numSign !== denSign), new BigInteger(remainder, numSign)];
  }

  function divmodSmall(dividend, divisor) {
    let length = dividend.length,
      quotient = createArray(length),
      remainder = 0,
      i;

    for (i = length - 1; i >= 0; i--) {
      let combined = remainder * BASE + dividend[i];
      let q = Math.floor(combined / divisor);
      remainder = combined - q * divisor;
      quotient[i] = q | 0;
    }

    return [quotient, remainder];
  }

  function compare(x, y) {
    let i = x.length;
    if (i !== y.length) {
      return x.length > y.length ? 1 : -1;
    }
    while (i--) {
      if (x[i] !== y[i]) {
        return x[i] > y[i] ? 1 : -1;
      }
    }
    return 0;
  }

  function square(value) {
    let valueLength = value.length;
    let result = createArray(valueLength + valueLength);
    let i, j, carry;

    for (i = 0; i < valueLength; i++) {
      carry = 0;
      for (j = 0; j < valueLength; j++) {
        let product = value[i] * value[j] + result[i + j] + carry;
        carry = Math.floor(product / BASE);
        result[i + j] = product - carry * BASE;