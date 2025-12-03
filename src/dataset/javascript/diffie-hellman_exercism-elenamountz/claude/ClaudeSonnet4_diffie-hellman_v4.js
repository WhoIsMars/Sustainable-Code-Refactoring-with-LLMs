export class DiffieHellman {
  constructor(p, g) {
    if (p <= 1 || g <= 1 || !this.isPrime(p) || !this.isPrime(g)) {
      throw new Error();
    }
    this.p = p;
    this.g = g;
  }

  isPrime(number) {
    if (number <= 1) return false;
    if (number <= 3) return true;
    if (number % 2 === 0 || number % 3 === 0) return false;
    
    const sqrt = Math.sqrt(number);
    for (let i = 5; i <= sqrt; i += 6) {
      if (number % i === 0 || number % (i + 2) === 0) {
        return false;
      }
    }
    return true;
  }

  getPublicKeyFromPrivateKey(privateKey) {
    if (privateKey <= 1 || privateKey >= this.p) {
      throw new Error();
    }
    return this.modPow(this.g, privateKey, this.p);
  }

  getSharedSecret(privateKey, publicKey) {
    return this.modPow(publicKey, privateKey, this.p);
  }

  modPow(base, exponent, modulus) {
    if (modulus === 1) return 0;
    let result = 1;
    base %= modulus;
    while (exponent > 0) {
      if (exponent & 1) {
        result = (result * base) % modulus;
      }
      exponent >>= 1;
      base = (base * base) % modulus;
    }
    return result;
  }
}