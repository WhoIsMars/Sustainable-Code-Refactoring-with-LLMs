class DiffieHellman {
    constructor(p, g) {
        if (!(1 <= p && p < 9999) || !(1 <= g && g < 9999)) {
            throw new Error("Arguments are out of range");
        } else if (!this.isPrime(p) || !this.isPrime(g)) {
            throw new Error("Arguments are not prime");
        }

        this.p = p;
        this.g = g;
    }

    getPublicKeyFromPrivateKey(a) {
        if (!(2 <= a && a < this.p)) {
            throw new Error("Not a valid private key");
        }

        return this.modPow(this.g, a, this.p);
    }

    getSharedSecret(priv, pub) {
        return this.modPow(pub, priv, this.p);
    }

    isPrime(num) {
        if (num <= 1) return false;
        if (num <= 3) return true;
        if (num % 2 === 0 || num % 3 === 0) return false;

        for (let i = 5; i * i <= num; i += 6) {
            if (num % i === 0 || num % (i + 2) === 0) return false;
        }

        return true;
    }

    modPow(base, exponent, modulus) {
        if (modulus === 1) return 0;
        let result = 1;
        base = base % modulus;
        while (exponent > 0) {
            if (exponent % 2 === 1) result = (result * base) % modulus;
            exponent = exponent >> 1; // Equivalent to exponent /= 2, but faster
            base = (base * base) % modulus;
        }
        return result;
    }
}

module.exports = DiffieHellman;