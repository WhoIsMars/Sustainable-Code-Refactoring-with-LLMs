export default class DiffieHellman {
  private _p: number;
  private _g: number;

  private isPrime(num: number): boolean {
    if (num < 2) return false;
    if (num === 2 || num === 3) return true;
    if (num % 2 === 0 || num % 3 === 0) return false;
    for (let i = 5, limit = Math.sqrt(num); i <= limit; i += 6) {
      if (num % i === 0 || num % (i + 2) === 0) return false;
    }
    return true;
  }

  constructor(p: number, g: number) {
    if (this.isPrime(p) && this.isPrime(g)) {
      this._p = p;
      this._g = g;
    } else {
      throw new Error('Inputs must be prime');
    }
  }

  public getPublicKeyFromPrivateKey(privateKeyA: number): number {
    if (privateKeyA <= 1 || privateKeyA >= this._p) {
      throw new Error('Invalid private key');
    }
    return this.modularExponentiation(this._g, privateKeyA, this._p);
  }

  public getSharedSecret(privateKeyA: number, publicKeyB: number): number {
    if (privateKeyA <= 1 || privateKeyA >= this._p) {
      throw new Error('Invalid private key');
    }
    return this.modularExponentiation(publicKeyB, privateKeyA, this._p);
  }

  private modularExponentiation(base: number, exponent: number, modulus: number): number {
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
}