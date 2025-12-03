export default class DiffieHellman {
  readonly p: number;
  readonly g: number;

  constructor(p: number, g: number) {
    if (p < 2 || g >= p) {
      throw new Error('Arguments out of range');
    }
    if (!this.isPrime(p) || !this.isPrime(g)) {
      throw new Error('Arguments are not prime');
    }
    if (!this.isPrimitiveRootModulo(p, g)) {
      throw new Error(`${g} is not a primitive root modulo of ${p}`);
    }
    this.p = p;
    this.g = g;
  }

  private isPrime(num: number): boolean {
    if (num <= 1) return false;
    if (num <= 3) return true;

    if (num % 2 === 0 || num % 3 === 0) return false;

    for (let i = 5; i * i <= num; i = i + 6) {
      if (num % i === 0 || num % (i + 2) === 0) return false;
    }

    return true;
  }

  private isPrimitiveRootModulo(p: number, g: number): boolean {
    const phi = p - 1;
    const primeFactors = this.primeFactors(phi);

    for (const factor of primeFactors) {
      if (this.power(g, phi / factor, p) === 1) {
        return false;
      }
    }

    return true;
  }

  private primeFactors(n: number): number[] {
    const factors: number[] = [];
    let num = n;

    while (num % 2 === 0) {
      factors.push(2);
      num /= 2;
    }

    for (let i = 3; i * i <= num; i += 2) {
      while (num % i === 0) {
        factors.push(i);
        num /= i;
      }
    }

    if (num > 2) {
      factors.push(num);
    }

    return [...new Set(factors)];
  }

  private power(base: number, exponent: number, modulus: number): number {
    let result = 1;
    base = base % modulus;

    while (exponent > 0) {
      if (exponent % 2 === 1) result = (result * base) % modulus;

      base = (base * base) % modulus;
      exponent = Math.floor(exponent / 2);
    }

    return result;
  }

  getPublicKeyFromPrivateKey(privateKey: number): number {
    if (privateKey < 2 || privateKey >= this.p) {
      throw new Error(
        `Private key must be greater than one and less than modulus parameter, ${this.p}`
      );
    }
    return this.power(this.g, privateKey, this.p);
  }

  getSharedSecret(aPrivateKey: number, bPublicKey: number): number {
    return this.power(bPublicKey, aPrivateKey, this.p);
  }
}