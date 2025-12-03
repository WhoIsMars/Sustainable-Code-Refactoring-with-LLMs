export class DiffieHellman {

  constructor(p, g){
    if (p <= 1 || g <= 1) {
      throw new Error("p and g must be greater than 1");
    }
    if (!this.isPrime(p) || !this.isPrime(g)) {
      throw new Error("p and g must be prime numbers");
    }

    this.p = p;
    this.g = g;
  }

  isPrime(number) {
    if (number <= 1) return false;
    if (number <= 3) return true;

    if (number % 2 === 0 || number % 3 === 0) return false;

    for (let i = 5; i * i <= number; i += 6) {
      if (number % i === 0 || number % (i + 2) === 0) return false;
    }

    return true;
  }

  getPublicKeyFromPrivateKey(privateKey) {
    if (privateKey <= 1 || privateKey >= this.p) {
      throw new Error("Private key must be between 1 and p");
    }
    return this.modularPow(this.g, privateKey, this.p);
  }

  getSharedSecret(privateKey, publicKey) {
    return this.modularPow(publicKey, privateKey, this.p);
  }

  modularPow(base, exponent, modulus) {
    if (modulus === 1) return 0;
    let result = 1;
    base = base % modulus;
    while (exponent > 0) {
      if (exponent % 2 === 1) result = (result * base) % modulus;
      exponent = exponent >> 1; // Equivalent to exponent /= 2
      base = (base * base) % modulus;
    }
    return result;
  }
}