class DiffieHellman {
    constructor(p, g) {
        if (!(1 <= p && p < 9999) || !(1 <= g && g < 9999)) {
            throw new Error("Arguments are out of range");
        }
        if (!DiffieHellman.isPrime(p) || !DiffieHellman.isPrime(g)) {
            throw new Error("Arguments are not prime");
        }

        this.p = p;
        this.g = g;
    }

    getPublicKeyFromPrivateKey(a) {
        if (!(2 <= a && a < this.p)) {
            throw new Error("Not a valid private key");
        }

        return this.modularExponentiation(this.g, a, this.p);
    }

    getSharedSecret(priv, pub) {
        return this.modularExponentiation(pub, priv, this.p);
    }

    static isPrime(num) {
        if (num < 2) return false;
        if (num === 2 || num === 3) return true;
        if (num % 2 === 0 || num % 3 === 0) return false;
        for (let i = 5, limit = Math.sqrt(num); i <= limit; i += 6) {
            if (num % i === 0 || num % (i + 2) === 0) return false;
        }
        return true;
    }

    modularExponentiation(base, exponent, modulus) {
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

module.exports = DiffieHellman;