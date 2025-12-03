export class DiffieHellman {

  // p and g have to be greater than 1 and prime numbers
  // Otherwise, a new error must be thrown
  constructor(p, g){
    if(p <= 1 || g <= 1){
      throw new Error();
    } else if(!(this.isPrime(p)) || !(this.isPrime(g))){
      throw new Error();
    } else {
      this.p = p;
      this.g = g;
    }
  }

  // Check if the input is a prime number
  isPrime(number){
    if(number <= 1) return false;
    if(number <= 3) return true;
    if(number % 2 === 0 || number % 3 === 0) return false;
    
    for(let i = 5; i * i <= number; i += 6){
      if(number % i === 0 || number % (i + 2) === 0){
        return false;
      }
    }
    return true;
  }

  // Modular exponentiation using binary exponentiation
  modPow(base, exponent, modulus) {
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

  // Generate public key using the private one
  getPublicKeyFromPrivateKey(privateKey){
    if(privateKey > 1 && privateKey < this.p){
      return this.modPow(this.g, privateKey, this.p);
    }
    throw new Error();
  }

  // Calculate Alice's and Bob's shared secret key
  // The shared secret key is the same for both of them
  getSharedSecret(privateKey, publicKey){
    return this.modPow(publicKey, privateKey, this.p);
  }
}