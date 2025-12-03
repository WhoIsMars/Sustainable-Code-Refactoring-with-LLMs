export default class DiffieHellman {
  private _p: number;
  private _g: number;

  private isPrime(num: number): boolean {
    if (num < 2) return false;
    if (num === 2) return true;
    if (num % 2 === 0) return false;
    
    const sqrt = Math.sqrt(num);
    for (let i = 3; i <= sqrt; i += 2) {
      if (num % i === 0) return false;
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

  constructor(p: number, g: number) {
    if (this.isPrime(p) && this.isPrime(g)) {
      this._p = p;
      this._g = g;
    } else {
      throw 'Inputs must be prime';
    }
  }

  public getPublicKeyFromPrivateKey(privateKeyA: number): number {
    if (privateKeyA <= 1 || privateKeyA >= this._p) {
      throw 'Invalid private key';
    }
    return this.modPow(this._g, privateKeyA, this._p);
  }

  public getSharedSecret(privateKeyA: number, publicKeyB: number): number {
    if (privateKeyA <= 1 || privateKeyA >= this._p) {
      throw 'Invalid private key';
    }
    return this.modPow(publicKeyB, privateKeyA, this._p);
  }
}