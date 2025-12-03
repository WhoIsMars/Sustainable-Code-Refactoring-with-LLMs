export default class Rational {
  constructor(private a: number, private b: number) {}

  private static gcd(x: number, y: number): number {
    while (y !== 0) {
      [x, y] = [y, x % y];
    }
    return Math.abs(x);
  }

  public reduce(rational: Rational = new Rational(this.a, this.b)): Rational {
    const gcd = Rational.gcd(rational.a, rational.b);
    const sign = rational.b < 0 ? -1 : 1;
    return new Rational((rational.a / gcd) * sign, (rational.b / gcd) * sign);
  }

  public add(rational: Rational): Rational {
    const numerator = this.a * rational.b + rational.a * this.b;
    const denominator = this.b * rational.b;
    return this.reduce(new Rational(numerator, denominator));
  }

  public sub(rational: Rational): Rational {
    return this.add(new Rational(-rational.a, rational.b));
  }

  public mul(rational: Rational): Rational {
    return this.reduce(new Rational(this.a * rational.a, this.b * rational.b));
  }

  public div(rational: Rational): Rational {
    if (rational.a === 0) throw new Error("Cannot divide by zero");
    return this.reduce(new Rational(this.a * rational.b, this.b * rational.a));
  }

  public abs(): Rational {
    return this.reduce(new Rational(Math.abs(this.a), Math.abs(this.b)));
  }

  public exprational(power: number): Rational {
    if (power === 0) return new Rational(1, 1);
    const absPower = Math.abs(power);
    const numerator = power > 0 ? this.a ** absPower : this.b ** absPower;
    const denominator = power > 0 ? this.b ** absPower : this.a ** absPower;
    return this.reduce(new Rational(numerator, denominator));
  }

  public expreal(base: number): number {
    return Math.pow(base, this.a / this.b);
  }
}