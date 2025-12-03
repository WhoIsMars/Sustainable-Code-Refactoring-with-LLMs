var bigInt = function (e) {
  'use strict';

  const BASE = 1e7;
  const BASE_LOG = 7;
  const MAX_SAFE = 9007199254740992;
  const MAX_SAFE_LOG = Math.log(MAX_SAFE);

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
    return -MAX_SAFE < num && num < MAX_SAFE;
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
    let xLen = x.length;
    let yLen = y.length;
    const result = new Array(xLen);
    let carry = 0;
    let sum, i;

    for (i = 0; i < yLen; i++) {
      sum = x[i] + y[i] + carry;
      carry = sum >= BASE ? 1 : 0;
      result[i] = sum - carry * BASE;
    }

    while (i < xLen) {
      sum = x[i] + carry;
      carry = sum === BASE ? 1 : 0;
      result[i++] = sum - carry * BASE;
    }

    if (carry > 0) {
      result.push(carry);
    }

    return result;
  }

  function add(x, y) {
    return x.length >= y.length ? fastAdd(x, y) : fastAdd(y, x);
  }

  function subtract(x, y) {
    let xLen = x.length;
    const result = new Array(xLen);
    let borrow = 0;
    let diff;

    for (let i = 0; i < xLen; i++) {
      diff = x[i] - borrow - (y[i] || 0);
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

  function fastSubtract(x, y, negate) {
    let result = subtract(x, y);
    return typeof result === 'number' ? (negate ? -result : result) : new BigInteger(result, negate);
  }

  function multiply(x, y) {
    let xLen = x.length;
    let yLen = y.length;
    let productSize = xLen + yLen;
    let product = createArray(productSize);
    let carry, i, j, term;

    for (i = 0; i < xLen; i++) {
      carry = 0;
      for (j = 0; j < yLen; j++) {
        term = x[i] * y[j] + product[i + j] + carry;
        carry = Math.floor(term / BASE);
        product[i + j] = term - carry * BASE;
      }
      product[i + yLen] += carry;
    }

    trim(product);
    return product;
  }

  function simpleDivision(dividend, divisor) {
    let result = createArray(dividend.length);
    let remainder = 0;

    for (let i = dividend.length - 1; i >= 0; i--) {
      let term = remainder * BASE + dividend[i];
      let quotient = Math.floor(term / divisor);
      remainder = term - quotient * divisor;
      result[i] = quotient;
    }

    trim(result);
    return [result, remainder];
  }

  function compare(x, y) {
    let xLen = x.length;
    let yLen = y.length;

    if (xLen !== yLen) {
      return xLen > yLen ? 1 : -1;
    }

    for (let i = xLen - 1; i >= 0; i--) {
      if (x[i] !== y[i]) {
        return x[i] > y[i] ? 1 : -1;
      }
    }

    return 0;
  }

  function bigIntFn(e, t) {
    if (e instanceof BigInteger || e instanceof SmallInteger) return e;
    if (typeof e === 'number') {
      if (isSmall(e)) return new SmallInteger(e);
      e = String(e);
    }
    if (typeof e === 'string') {
      let sign = e[0] === '-';
      if (sign) e = e.slice(1);

      let baseIndex = e.indexOf('e');
      if (baseIndex > -1) {
        let base = e.substring(0, baseIndex);
        let exponent = parseInt(e.substring(baseIndex + 1));
        if (exponent > 100) {
          throw new Error("Exponent too large");
        }
        e = base + Array(exponent + 1).join("0");
      }

      let digits = [];
      for (let i = e.length; i > 0; i -= BASE_LOG) {
        let chunk = e.substring(Math.max(i - BASE_LOG, 0), i);
        digits.push(parseInt(chunk));
      }
      return new BigInteger(digits, sign);
    }
    return W[0];
  }

  BigInteger.prototype.add = function (e) {
    let n = bigIntFn(e);
    if (this.sign !== n.sign) return this.subtract(n.negate());
    let r = this.value,
      i = n.value;
    return n.isSmall ? new BigInteger(fastAdd(r, toBaseArray(Math.abs(n.value))), this.sign) : new BigInteger(fastAdd(r, i), this.sign);
  };
  BigInteger.prototype.plus = BigInteger.prototype.add;
  SmallInteger.prototype.add = function (e) {
    let t = bigIntFn(e),
      n = this.value;
    if (n < 0 !== t.sign) return this.subtract(t.negate());
    let r = t.value;
    if (t.isSmall) {
      if (isSmall(n + r)) return new SmallInteger(n + r);
      r = toBaseArray(Math.abs(r));
    }
    return new BigInteger(fastAdd(r, toBaseArray(Math.abs(n))), n < 0);
  };
  SmallInteger.prototype.plus = SmallInteger.prototype.add;
  BigInteger.prototype.subtract = function (e) {
    let t = bigIntFn(e);
    if (this.sign !== t.sign) return this.add(t.negate());
    let n = this.value,
      r = t.value;
    return t.isSmall ? fastSubtract(n, toBaseArray(Math.abs(t.value)), this.sign) : compare(n, r) >= 0 ? fastSubtract(n, r, this.sign) : new BigInteger(subtract(r, n), !this.sign);
  };
  BigInteger.prototype.minus = BigInteger.prototype.subtract;
  SmallInteger.prototype.subtract = function (e) {
    let t = bigIntFn(e),
      n = this.value;
    if (n < 0 !== t.sign) return this.add(t.negate());
    let r = t.value;
    return t.isSmall ? new SmallInteger(n - r) : compare(r, toBaseArray(Math.abs(n))) >= 0 ? new BigInteger(subtract(r, toBaseArray(Math.abs(n))), n >= 0) : fastSubtract(toBaseArray(Math.abs(n)), r, n >= 0);
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
  BigInteger.prototype.multiply = function (e) {
    let n = bigIntFn(e),
      r = this.value,
      i = n.value,
      u = this.sign !== n.sign;
    if (n.isSmall) {
      if (i === 0) return W[0];
      if (i === 1) return this;
      if (i === -1) return this.negate();
      i = Math.abs(i);
      if (i < BASE) return new BigInteger(multiply(r, toBaseArray(i)), u);
      i = toBaseArray(i);
    }
    return new BigInteger(multiply(r, i), u);
  };
  BigInteger.prototype.times = BigInteger.prototype.multiply;
  SmallInteger.prototype.multiply = function (e) {
    let n = bigIntFn(e),
      r = this.value,
      i = n.value;
    if (r === 0) return W[0];
    if (r === 1) return n;
    if (r === -1) return n.negate();
    if (n.isSmall) {
      if (isSmall(r * i)) return new SmallInteger(r * i);
      i = toBaseArray(Math.abs(i));
    }
    let s = Math.abs(r);
    return new BigInteger(multiply(i, toBaseArray(s)), this.sign !== n.sign);
  };
  SmallInteger.prototype.times = SmallInteger.prototype.multiply;
  BigInteger.prototype.square = function () {
    return new BigInteger(multiply(this.value, this.value), false);
  };
  SmallInteger.prototype.square = function () {
    let e = this.value * this.value;
    return isSmall(e) ? new SmallInteger(e) : new BigInteger(multiply(toBaseArray(Math.abs(this.value)), toBaseArray(Math.abs(this.value))), false);
  };
  BigInteger.prototype.divmod = function (e) {
    let t = divide(this, e);
    return {
      quotient: t[0],
      remainder: t[1]
    };
  };
  SmallInteger.prototype.divmod = BigInteger.prototype.divmod;
  BigInteger.prototype.divide = function (e) {
    return divide(this, e)[0];
  };
  SmallInteger.prototype.over = SmallInteger.prototype.divide = BigInteger.prototype.over = BigInteger.prototype.divide;
  BigInteger.prototype.mod = function (e) {
    return divide(this, e)[1];
  };
  SmallInteger.prototype.remainder = SmallInteger.prototype.mod = BigInteger.prototype.remainder = BigInteger.prototype.mod;
  BigInteger.prototype.pow = function (e) {
    let t = bigIntFn(e),
      n = this.value,
      r, i, s;
    if (t.value === 0) return W[1];
    if (n === 0) return W[0];
    if (n === 1) return W[1];
    if (n === -1) return t.isEven() ? W[1] : W[-1];
    if (t.sign) return W[0];
    if (!t.isSmall) throw new Error('The exponent ' + t.toString() + ' is too large.');
    if (this.isSmall && isSmall(i = Math.pow(n, t.value))) return new SmallInteger(i);
    s = this, r = W[1];
    for (;;) {
      t.value & !0 && (r = r.times(s), --t.value);
      if (t.value === 0) break;
      t.value /= 2, s = s.square();
    }
    return r;
  };
  SmallInteger.prototype.pow = BigInteger.prototype.pow;
  BigInteger.prototype.compareAbs = function (e) {
    let t = bigIntFn(e),
      n = this.value,
      r = t.value;
    return t.isSmall ? 1 : compare(n, r);
  };
  SmallInteger.prototype.compareAbs = function (e) {
    let t = bigIntFn(e),
      n = Math.abs(this.value),
      r = t.value;
    return t.isSmall ? (r = Math.abs(r), n === r ? 0 : n > r ? 1 : -1) : -1;
  };
  BigInteger.prototype.compare = function (e) {
    let t = bigIntFn(e),
      n = this.value,
      r = t.value;
    return this.sign !== t.sign ? t.sign ? 1 : -1 : t.isSmall ? this.sign ? -1 : 1 : compare(n, r) * (this.sign ? -1 : 1);
  };
  BigInteger.prototype.compareTo = BigInteger.prototype.compare;
  SmallInteger.prototype.compare = function (e) {
    let t = bigIntFn(e),
      n = this.value,
      r = t.value;
    return t.isSmall ? n == r ? 0 : n > r ? 1 : -1 : n < 0 !== t.sign ? n < 0 ? -1 : 1 : n < 0 ? 1 : -1;
  };
  SmallInteger.prototype.compareTo = SmallInteger.prototype.compare;
  BigInteger.prototype.equals = function (e) {
    return this.compare(e) === 0;
  };
  SmallInteger.prototype.eq = SmallInteger.prototype.equals = BigInteger.prototype.eq = BigInteger.prototype.equals;
  BigInteger.prototype.notEquals = function (e) {
    return this.compare(e) !== 0;
  };
  SmallInteger.prototype.neq = SmallInteger.prototype.notEquals = BigInteger.prototype.neq = BigInteger.prototype.notEquals;
  BigInteger.prototype.greater = function (e) {
    return this.compare(e) > 0;
  };
  SmallInteger.prototype.gt = SmallInteger.prototype.greater = BigInteger.prototype.gt = BigInteger.prototype.greater;
  BigInteger.prototype.lesser = function (e) {
    return this.compare(e) < 0;
  };
  SmallInteger.prototype.lt = SmallInteger.prototype.lesser = BigInteger.prototype.lt = BigInteger.prototype.lesser;
  BigInteger.prototype.greaterOrEquals = function (e) {
    return this.compare(e) >= 0;
  };
  SmallInteger.prototype.geq = SmallInteger.prototype.greaterOrEquals = BigInteger.prototype.geq = BigInteger.prototype.greaterOrEquals;
  BigInteger.prototype.lesserOrEquals = function (e) {
    return this.compare(e) <= 0;
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
  BigInteger.prototype.isDivisibleBy = function (e) {
    let t = bigIntFn(e),
      n = t.value;
    return n === 0 ? false : n === 1 ? true : n === 2 ? this.isEven() : this.mod(t).equals(W[0]);
  };
  SmallInteger.prototype.isDivisibleBy = BigInteger.prototype.isDivisibleBy;
  BigInteger.prototype.isPrime = function () {
    let e = this.abs(),
      t = e.prev();
    if (e.isUnit()) return false;
    if (e.equals(2) || e.equals(3) || e.equals(5)) return true;
    if (e.isEven() || e.isDivisibleBy(3) || e.isDivisibleBy(5)) return false;
    if (e.lesser(25)) return true;
    let n = [2, 3, 5, 7, 11, 13, 17, 19],
      r = t,
      i, s, o, u;
    while (r.isEven()) r = r.divide(2);
    for (o = 0; o < n.length; o++) {
      u = bigIntFn(n[o]).modPow(r, e);
      if (u.equals(W[1]) || u.equals(t)) continue;
      for (s = true, i = r; s && i.lesser(t); i = i.multiply(2)) u = u.square().mod(e), u.equals(t) && (s = false);
      if (s) return false;
    }
    return true;
  };
  SmallInteger.prototype.isPrime = BigInteger.prototype.isPrime;
  BigInteger.prototype.next = function () {
    let e = this.value;
    return this.sign ? fastSubtract(e, toBaseArray(1), this.sign) : new BigInteger(fastAdd(e, toBaseArray(1)), this.sign);
  };
  SmallInteger.prototype.next = function () {
    let e = this.value;
    return e + 1 < MAX_SAFE ? new SmallInteger(e + 1) : new BigInteger(toBaseArray(MAX_SAFE), false);
  };
  BigInteger.prototype.prev = function () {
    let e = this.value;
    return this.sign ? new BigInteger(fastAdd(e, toBaseArray(1)), true) : fastSubtract(e, toBaseArray(1), this.sign);
  };
  SmallInteger.prototype.prev = function () {
    let e = this.value;
    return e - 1 > -MAX_SAFE ? new SmallInteger(e - 1) : new BigInteger(toBaseArray(MAX_SAFE), true);
  };
  let O = [1];
  while (O[O.length - 1] <= BASE) O.push(2 * O[O.length - 1]);
  let M = O.length,
    _ = O[M - 1];
  BigInteger.prototype.shiftLeft = function (e) {
    if (!isSmall(e)) return e.isNegative() ? this.shiftRight(e.abs()) : this.times(W[2].pow(e));
    e = +e;
    if (e < 0) return this.shiftRight(-e);
    let t = this;
    while (e >= M) t = t.multiply(_), e -= M - 1;
    return t.multiply(O[e]);
  };
  SmallInteger.prototype.shiftLeft = BigInteger.prototype.shiftLeft;
  BigInteger.prototype.shiftRight = function (e) {
    let t;
    if (!isSmall(e)) return e.isNegative() ? this.shiftLeft(e.abs()) : (t = this.divmod(W[2].pow(e)), t.remainder.isNegative() ? t.quotient.prev() : t.quotient);
    e = +e;
    if (e < 0) return this.shiftLeft(-e);
    let n = this;
    while (e >= M) {
      if (n.isZero()) return n;
      t = divide(n, _), n = t[1].isNegative() ? t[0].prev() : t[0], e -= M - 1;
    }
    return t = divide(n, O[e]), t[1].isNegative() ? t[0].prev() : t[0];
  };
  SmallInteger.prototype.shiftRight = BigInteger.prototype.shiftRight;
  BigInteger.prototype.toString = function (t) {
    t === e && (t = 10);
    if (t !== 10) return toString(this, t);
    let n = this.value,
      r = n.length,
      i = String(n[--r]),
      s = '0000000',
      o;
    while (--r >= 0) o = String(n[r]), i += s.slice(o.length) + o;
    let u = this.sign ? '-' : '';
    return u + i;
  };
  SmallInteger.prototype.toString = function (t) {
    return t === e && (t = 10), t != 10 ? toString(this, t) : String(this.value);
  };
  BigInteger.prototype.valueOf = function () {
    return +this.toString();
  };
  BigInteger.prototype.toJSNumber = BigInteger.prototype.valueOf;
  SmallInteger.prototype.valueOf = function () {
    return this.value;
  };
  SmallInteger.prototype.toJSNumber = SmallInteger.prototype.valueOf;

  function divide(e, n) {
    let r, i = bigIntFn(n),
      s = e.value,
      a = i.value,
      c;
    if (a === 0) throw new Error('Cannot divide by zero');
    if (e.isSmall) return i.isSmall ? [new SmallInteger(Math.trunc(s / a)), new SmallInteger(s % a)] : [W[0], e];
    if (i.isSmall) {
      if (a === 1) return [e, W[0]];
      if (a == -1) return [e.negate(), W[0]];
      let h = Math.abs(a);
      if (h < BASE) {
        r = simpleDivision(s, h), c = r[0];
        let d = r[1];
        return e.sign && (d = -d), typeof c == 'number' ? (e.sign !== i.sign && (c = -c), [new SmallInteger(c), new SmallInteger(d)]) : [new BigInteger(c, e.sign !== i.sign), new SmallInteger(d)];
      }
      a = toBaseArray(h);
    }
    let v = compare(s, a);
    if (v === -1) return [W[0], e];
    if (v === 0) return [W[e.sign === i.sign ? 1 : -1], W[0]];
    r = longDivision(s, a), c = r[0];
    let m = e.sign !== i.sign,
      g = r[1],
      y = e.sign;
    return typeof c == 'number' ? (m && (c = -c), c = new SmallInteger(c)) : c = new BigInteger(c, m), typeof g == 'number' ? (y && (g = -g), g = new SmallInteger(g)) : g = new BigInteger(g, y), [c, g];
  }

  function longDivision(e, n) {
    let r = e.length,
      i = n.length,
      s = [],
      o = [],
      u = BASE,
      a, f, c, h, p;
    while (r) {
      o.unshift(e[--r]);
      if (compare(o, n) < 0) {
        s.push(0);
        continue;
      }
      f = o.length, c = o[f - 1] * u + o[f - 2], h = n[i - 1] * u + n[i - 2], f > i && (c = (c + 1) * u), a = Math.ceil(c / h);
      do {
        p = multiply(n, toBaseArray(a));
        if (compare(p, o) <= 0) break;
        a--;
      } while (a);
      s.push(a), o = subtract(o, p);
    }
    return s.reverse(), [toInteger(s), toInteger(o)];
  }

  function toInteger(e) {
    let t = e.length;
    if (t < 4 && compare(e, toBaseArray(MAX_SAFE)) < 0) switch (t) {
      case 0:
        return 0;
      case 1:
        return e[0];
      case 2:
        return e[0] + e[1] * BASE;
      default:
        return e[0] + (e[1] + e[2] * BASE) * BASE;
    }
    return e;
  }

  function toString(e, t) {
    t = bigIntFn(t);
    if (t.isZero()) {
      if (e.isZero()) return '0';
      throw new Error('Cannot convert nonzero numbers to base 0.');
    }
    if (t.equals(-1)) return e.isZero() ? '0' : e.isNegative() ? new Array(1 - e).join('10') : '1' + new Array(+e).join('01');
    let n = '';
    e.isNegative() && t.isPositive() && (n = '-', e = e.abs());
    if (t.equals(1)) return e.isZero() ? '0' : n + new Array(+e + 1).join(1);
    let r = [],
      i = e,
      s;
    while (i.isNegative() || compare(i.value, t.value) >= 0) {
      s = divide(i, t), i = s[0];
      let o = s[1];
      o.isNegative() && (o = t.minus(o).abs(), i = i.next()), r.push(R(o));
    }
    return r.push(R(i)), n + r.reverse().join('');
  }

  function R(e) {
    let t = e.value;
    return typeof t == 'number' && t <= 36 ? '0123456789abcdefghijklmnopqrstuvwxyz'.charAt(t) : '<' + t + '>';
  }
  let W = function (e, t) {
    return typeof e == 'undefined' ? W[0] : typeof t != 'undefined' ? +t === 10 ? bigIntFn(e) : parseBase(e, t) : bigIntFn(e);
  };

  function parseBase(e, t) {
    let n = W[0],
      r = W[1],
      i = e.length;
    if (2 <= t && t <= 36 && i <= MAX_SAFE_LOG / Math.log(t)) return new SmallInteger(parseInt(e, t));
    t = bigIntFn(t);
    let o = [],
      a, f = e[0] === '-';
    for (a = f ? 1 : 0; a < e.length; a++) {
      let l = e[a].toLowerCase(),
        c = l.charCodeAt(0);
      if (48 <= c && c <= 57) o.push(bigIntFn(l));
      else if (97 <= c && c <= 122) o.push(bigIntFn(l.charCodeAt(0) - 87));
      else {
        if (l !== '<') throw new Error(l + ' is not a valid character');
        let h = a;
        do a++; while (e[a] !== '>');
        o.push(bigIntFn(e.slice(h + 1, a)));
      }
    }
    o.reverse();
    for (a = 0; a < o.length; a++) n = n.add(o[a].times(r)), r = r.times(t);
    return f ? n.negate() : n;
  }
  for (let X = 0; X < 1e3; X++) W[X] = new SmallInteger(X), X > 0 && (W[-X] = new SmallInteger(-X));
  return W.one = W[1], W.zero = W[0], W.minusOne = W[-1], W.isInstance = function (e) {
    return e instanceof BigInteger || e instanceof SmallInteger;
  }, W;
}();
typeof module != 'undefined' && module.hasOwnProperty('exports') && (module.exports = bigInt);