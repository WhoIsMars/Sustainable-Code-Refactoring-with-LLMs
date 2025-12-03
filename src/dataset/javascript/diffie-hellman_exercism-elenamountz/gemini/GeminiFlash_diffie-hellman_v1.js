export class DiffieHellman {

  constructor(p, g){
    if(p <= 1 || g <= 1){
      throw new Error("p and g must be greater than 1");
    }
    if(!this.isPrime(p) || !this.isPrime(g)){
      throw new Error("p and g must be prime numbers");
    }
    this.p = p;
    this.g = g;
  }

  isPrime(number){
    if (number <= 1) return false;
    if (number <= 3) return true;

    if (number % 2 === 0 || number % 3 === 0) return false;

    for (let i = 5; i * i <= number; i = i + 6) {
      if (number % i === 0 || number % (i + 2) === 0)
        return false;
    }

    return true;
  }

  getPublicKeyFromPrivateKey(privateKey){
    if(privateKey < 2 || privateKey >= this.p){
      throw new Error("Private key must be between 2 and p-1");
    }
    return this.power(this.g, privateKey, this.p);
  }

  getSharedSecret(privateKey, publicKey){
    return this.power(publicKey, privateKey, this.p);
  }

  power(base, exponent, modulus) {
    let result = 1;
    base = base % modulus;
    while (exponent > 0) {
      if (exponent % 2 === 1)
        result = (result * base) % modulus;
      exponent = exponent >> 1;
      base = (base * base) % modulus;
    }
    return result;
  }
}