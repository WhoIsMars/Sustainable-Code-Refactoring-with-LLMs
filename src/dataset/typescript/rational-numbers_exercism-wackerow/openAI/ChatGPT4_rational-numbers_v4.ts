export default class Rational {
  constructor(private a: number, private b: number) {}

  private static gcd(x: number, y: number): number {
    while (y !== 0) {
      [x, y] = [y, x % y];
    }
    return Math.abs(x);
  }

  public reduce(rational: Rational = this): Rational {
    const gcd = Rational.gcd(rational.a, rational.b);
    const sign = rational.b < 0 ? -1 : 1;
    return new Rational((rational.a / gcd) * sign, (rational.b / gcd) * sign);
  }

  public add(rational: Rational): Rational {
    const numerator = this.a * rational.b + rational.a * this.b;
    const denominator = this.b * rational.b;
    return new Rational(numerator, denominator).reduce();
  }

  public sub(rational: Rational): Rational {
    return this.add(new Rational(-rational.a, rational.b));
  }

  public mul(rational: Rational): Rational {
    return new Rational(this.a * rational.a, this.b * rational.b).reduce();
  }

  public div(rational: Rational): Rational {
    if (rational.a === 0) throw new Error("Cannot divide by zero");
    return new Rational(this.a * rational.b, this.b * rational.a).reduce();
  }

  public abs(): Rational {
    return new Rational(Math.abs(this.a), Math.abs(this.b)).reduce();
  }

  public exprational(power: number): Rational {
    if (power === 0) return new Rational(1, 1);
    const absPower = Math.abs(power);
    const numerator = power > 0 ? this.a ** absPower : this.b ** absPower;
    const denominator = power > 0 ? this.b ** absPower : this.a ** absPower;
    return new Rational(numerator, denominator).reduce();
  }

  public expreal(base: number): number {
    return Math.pow(base, this.a / this.b);
  }
}