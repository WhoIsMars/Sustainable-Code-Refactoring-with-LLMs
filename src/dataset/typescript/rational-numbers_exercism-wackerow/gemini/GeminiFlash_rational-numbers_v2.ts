export default class Rational {
  // this.a === numerator
  // this.b === denominator
  constructor(private a: number, private b: number) {}

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
  
  // Reduce to lowest terms (integer / integer)
  public reduce(rational: Rational = new Rational(this.a, this.b)): Rational {
    const gcdValue = this.gcd(rational.a, rational.b);
    let reducedNumerator = rational.a / gcdValue;
    let reducedDenominator = rational.b / gcdValue;

    if (reducedDenominator < 0) {
      reducedNumerator = -reducedNumerator;
      reducedDenominator = -reducedDenominator;
    }

    return new Rational(reducedNumerator, reducedDenominator);
  }

  // Addition
  public add(rational: Rational): Rational {
    const numerator = this.a * rational.b + rational.a * this.b;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  // Subtraction
  public sub(rational: Rational): Rational {
    const numerator = this.a * rational.b - rational.a * this.b;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  // Multiplication
  public mul(rational: Rational): Rational {
    const numerator = this.a * rational.a;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  // Division (no divide by zero!)
  public div(rational: Rational): Rational {
    if (rational.a === 0) { throw "Cannot divide by zero" }
    const numerator = this.a * rational.b;
    const denominator = this.b * rational.a;
    return this.reduce(new Rational(numerator, denominator));
  }

  // Abs Value
  public abs(): Rational {
    return new Rational(Math.abs(this.a), Math.abs(this.b)).reduce();
  }

  // Exponentiation of rational number
  public exprational(power: number): Rational {
    if (power === 0) { return new Rational(1, 1) }

    let numerator: number;
    let denominator: number;

    if (power > 0) {
      numerator = this.a ** power;
      denominator = this.b ** power;
    } else {
      numerator = this.b ** Math.abs(power);
      denominator = this.a ** Math.abs(power);
    }

    return this.reduce(new Rational(numerator, denominator));
  }
  
  // Exponentiation of real number to a rational number
  public expreal(base: number): number {
    return Math.pow(base, this.a / this.b);
  }
}