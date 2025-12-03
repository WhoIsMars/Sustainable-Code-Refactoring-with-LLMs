export class DiffieHellman {
  constructor(p, g) {
    if (p <= 1 || g <= 1 || !DiffieHellman.isPrime(p) || !DiffieHellman.isPrime(g)) {
      throw new Error();
    }
    this.p = p;
    this.g = g;
  }

  static isPrime(number) {
    if (number < 2) return false;
    if (number === 2 || number === 3) return true;
    if (number % 2 === 0 || number % 3 === 0) return false;
    for (let i = 5, limit = Math.sqrt(number); i <= limit; i += 6) {
      if (number % i === 0 || number % (i + 2) === 0) return false;
    }
    return true;
  }

  getPublicKeyFromPrivateKey(privateKey) {
    if (privateKey > 1 && privateKey < this.p) {
      return BigInt(this.g) ** BigInt(privateKey) % BigInt(this.p);
    }
    throw new Error();
  }

  getSharedSecret(privateKey, publicKey) {
    return BigInt(publicKey) ** BigInt(privateKey) % BigInt(this.p);
  }
}