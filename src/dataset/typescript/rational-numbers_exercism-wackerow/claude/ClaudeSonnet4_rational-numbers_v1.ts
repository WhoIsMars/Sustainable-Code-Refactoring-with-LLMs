export default class Rational {
  // this.a === numerator
  // this.b === denominator
  constructor(private a: number, private b: number) {}
  
  // Euclidean algorithm for GCD - much more efficient
  private gcd(a: number, b: number): number {
    a = Math.abs(a);
    b = Math.abs(b);
    while (b !== 0) {
      const temp = b;
      b = a % b;
      a = temp;
    }
    return a;
  }
  
  // Reduce to lowest terms (integer / integer)
  public reduce(rational: Rational = new Rational(this.a, this.b)) {
    const gcd = this.gcd(rational.a, rational.b);
    // Tertiary to negate both numerator and denominator IF denominator negative
    const reducedNumerator = rational.b < 0 ? -rational.a / gcd : rational.a / gcd;
    const reducedDenominator = rational.b < 0 ? -rational.b / gcd: rational.b / gcd;
    return new Rational(reducedNumerator, reducedDenominator);
  }

  // Addition
  public add(rational: Rational): Rational {
    const numerator = this.a * rational.b + rational.a * this.b;
    const denominator = this.b * rational.b;
    // Return reduced result
    return this.reduce(new Rational(numerator, denominator));
  }

  // Subtraction
  public sub(rational: Rational): Rational {
    // Inline subtraction to avoid object creation
    const numerator = this.a * rational.b - rational.a * this.b;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  // Multiplication
  public mul(rational: Rational): Rational {
    const numerator = this.a * rational.a;
    const denominator = this.b * rational.b;
    // Return reduced result
    return this.reduce(new Rational(numerator, denominator));
  }

  // Division (no divide by zero!)
  public div(rational: Rational): Rational {
    // Throw error is dividing by zero
    if (rational.a === 0) { throw "Cannot divide by zero" }
    const numerator = this.a * rational.b;
    const denominator = this.b * rational.a;
    // Return reduced result
    return this.reduce(new Rational(numerator, denominator));
  }

  // Abs Value
  public abs(): Rational {
    const numerator = Math.abs(this.a);
    const denominator = Math.abs(this.b);
    // Return reduced result
    return this.reduce(new Rational(numerator, denominator));
  }

  // Exponentiation of rational number
  public exprational(power: number): Rational {
    // Anything to the power of 0 returns 1 / 1
    if (power === 0) { return new Rational(1, 1) }
    // If negative power, take reciprocal and use abs value
    const absPower = Math.abs(power);
    const numerator = power > 0
      ? this.a ** absPower
      : this.b ** absPower;
    const denominator = power > 0
      ? this.b ** absPower
      : this.a ** absPower;
    // Return reduced result
    return this.reduce(new Rational(numerator, denominator));
  }
  
  // Exponentiation of real number to a rational number
  public expreal(base: number): number {
    // Logarithms utilized to avoid division floating point errors
    return 2 ** (Math.log2(base ** this.a) / this.b);
  }
}