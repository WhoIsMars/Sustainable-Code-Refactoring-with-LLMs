export default class Rational {
  constructor(private a: number, private b: number) {}
  
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
  
  public reduce(rational: Rational = new Rational(this.a, this.b)): Rational {
    const gcd = this.gcd(rational.a, rational.b);
    const reducedNumerator = rational.b < 0 ? -rational.a / gcd : rational.a / gcd;
    const reducedDenominator = rational.b < 0 ? -rational.b / gcd: rational.b / gcd;
    return new Rational(reducedNumerator, reducedDenominator);
  }

  public add(rational: Rational): Rational {
    const numerator = this.a * rational.b + rational.a * this.b;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  public sub(rational: Rational): Rational {
    const numerator = this.a * rational.b - rational.a * this.b;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  public mul(rational: Rational): Rational {
    const numerator = this.a * rational.a;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  public div(rational: Rational): Rational {
    if (rational.a === 0) { throw "Cannot divide by zero" }
    const numerator = this.a * rational.b;
    const denominator = this.b * rational.a;
    return this.reduce(new Rational(numerator, denominator));
  }

  public abs(): Rational {
    const numerator = Math.abs(this.a);
    const denominator = Math.abs(this.b);
    return this.reduce(new Rational(numerator, denominator));
  }

  public exprational(power: number): Rational {
    if (power === 0) { return new Rational(1, 1) }
    const numerator = power > 0
      ? this.a ** power
      : this.b ** Math.abs(power);
    const denominator = power > 0
      ? this.b ** power
      : this.a ** Math.abs(power);
    return this.reduce(new Rational(numerator, denominator));
  }
  
  public expreal(base: number): number {
    return base ** (this.a / this.b);
  }
}