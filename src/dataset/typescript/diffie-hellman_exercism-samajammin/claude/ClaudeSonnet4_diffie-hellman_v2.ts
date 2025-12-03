export default class DiffieHellman {
  readonly p: number;
  readonly g: number;

  constructor(p: number, g: number) {
    if (p < 1 || g > p) {
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
    
    for (let i = 5; i * i <= num; i += 6) {
      if (num % i === 0 || num % (i + 2) === 0) {
        return false;
      }
    }
    return true;
  }

  private modPow(base: number, exponent: number, modulus: number): number {
    if (modulus === 1) return 0;
    let result = 1;
    base = base % modulus;
    while (exponent > 0) {
      if (exponent % 2 === 1) {
        result = (result * base) % modulus;
      }
      exponent = Math.floor(exponent / 2);
      base = (base * base) % modulus;
    }
    return result;
  }

  private isPrimitiveRootModulo(p: number, g: number): boolean {
    const seen = new Uint8Array(p);
    for (let i = 1; i < p; i++) {
      const value = this.modPow(g, i, p);
      if (seen[value]) return false;
      seen[value] = 1;
    }
    return true;
  }

  getPublicKeyFromPrivateKey(privateKey: number): number {
    if (privateKey < 2) {
      throw new Error('Private key must be greater than one');
    }
    if (privateKey >= this.p) {
      throw new Error(
        `Private key must be less than modulus parameter, ${this.p}`
      );
    }
    return this.modPow(this.g, privateKey, this.p);
  }

  getSharedSecret(aPrivateKey: number, bPublicKey: number): number {
    return this.modPow(bPublicKey, aPrivateKey, this.p);
  }
}