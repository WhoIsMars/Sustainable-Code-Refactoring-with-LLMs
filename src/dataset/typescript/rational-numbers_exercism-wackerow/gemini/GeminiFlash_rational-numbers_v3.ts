export default class Rational {
  constructor(private a: number, private b: number) {
    if (b === 0) {
      throw new Error("Denominator cannot be zero.");
    }
    if (!Number.isInteger(a) || !Number.isInteger(b)) {
      throw new Error("Numerator and denominator must be integers.");
    }
  }

  private gcd(a: number, b: number): number {
    a = Math.abs(a);
    b = Math.abs(b);
    while (b) {
      const temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }

  public reduce(): Rational {
    const commonDivisor = this.gcd(this.a, this.b);
    let reducedNumerator = this.a / commonDivisor;
    let reducedDenominator = this.b / commonDivisor;

    if (reducedDenominator < 0) {
      reducedNumerator = -reducedNumerator;
      reducedDenominator = -reducedDenominator;
    }

    return new Rational(reducedNumerator, reducedDenominator);
  }

  public add(rational: Rational): Rational {
    const numerator = this.a * rational.b + rational.a * this.b;
    const denominator = this.b * rational.b;
    return new Rational(numerator, denominator).reduce();
  }

  public sub(rational: Rational): Rational {
    const numerator = this.a * rational.b - rational.a * this.b;
    const denominator = this.b * rational.b;
    return new Rational(numerator, denominator).reduce();
  }

  public mul(rational: Rational): Rational {
    const numerator = this.a * rational.a;
    const denominator = this.b * rational.b;
    return new Rational(numerator, denominator).reduce();
  }

  public div(rational: Rational): Rational {
    if (rational.a === 0) {
      throw new Error("Cannot divide by zero");
    }
    const numerator = this.a * rational.b;
    const denominator = this.b * rational.a;
    return new Rational(numerator, denominator).reduce();
  }

  public abs(): Rational {
    return new Rational(Math.abs(this.a), Math.abs(this.b)).reduce();
  }

  public exprational(power: number): Rational {
    if (power === 0) {
      return new Rational(1, 1);
    }

    let numerator: number;
    let denominator: number;

    if (power > 0) {
      numerator = Math.pow(this.a, power);
      denominator = Math.pow(this.b, power);
    } else {
      numerator = Math.pow(this.b, Math.abs(power));
      denominator = Math.pow(this.a, Math.abs(power));
    }

    return new Rational(numerator, denominator).reduce();
  }

  public expreal(base: number): number {
    return Math.pow(base, this.a / this.b);
  }
}