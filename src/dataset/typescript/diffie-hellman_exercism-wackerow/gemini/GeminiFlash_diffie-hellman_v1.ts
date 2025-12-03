export default class DiffieHellman {
  private _p: number;
  private _g: number;

  private isPrime(num: number): boolean {
    if (num <= 1) return false;
    if (num <= 3) return true;
    if (num % 2 === 0 || num % 3 === 0) return false;
    for (let i = 5; i * i <= num; i = i + 6) {
      if (num % i === 0 || num % (i + 2) === 0) return false;
    }
    return true;
  }

  constructor(p: number, g: number) {
    if (!Number.isInteger(p) || !Number.isInteger(g)) {
        throw 'Inputs must be integers';
    }
    if (this.isPrime(p) && this.isPrime(g)) {
      [this._p, this._g] = [p, g];
    } else {
      throw 'Inputs must be prime';
    }
  }

  public getPublicKeyFromPrivateKey(privateKeyA: number): number {
    if (!Number.isInteger(privateKeyA)) {
        throw 'Private key must be an integer';
    }
    if (privateKeyA <= 1 || privateKeyA >= this._p) {
      throw 'Invalid private key';
    }
    return this.modPow(this._g, privateKeyA, this._p);
  }

  public getSharedSecret(privateKeyA: number, publicKeyB: number): number {
    if (!Number.isInteger(privateKeyA) || !Number.isInteger(publicKeyB)) {
        throw 'Private key and Public Key must be integers';
    }
    if (privateKeyA <= 1 || privateKeyA >= this._p) {
      throw 'Invalid private key';
    }
    return this.modPow(publicKeyB, privateKeyA, this._p);
  }

  private modPow(base: number, exponent: number, modulus: number): number {
    if (modulus === 1) return 0;
    let result = 1;
    base = base % modulus;
    while (exponent > 0) {
      if (exponent % 2 === 1) result = (result * base) % modulus;
      base = (base * base) % modulus;
      exponent = Math.floor(exponent / 2);
    }
    return result;
  }
}