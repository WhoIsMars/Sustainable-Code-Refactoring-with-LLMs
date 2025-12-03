class DiffieHellman {
    constructor(p, g) {
        if (!(1 <= p && p < 9999) || !(1 <= g && g < 9999))
            throw new Error("Arguments are out of range");
        else if (!this.prime(p) || !this.prime(g))
            throw new Error("Arguments are not prime");

        this.p = p;
        this.g = g;
    }

    getPublicKeyFromPrivateKey(a) {
        if (!(2 <= a && a < this.p)) throw new Error("Not a valid private key");

        return this.modPow(this.g, a, this.p);
    }

    getSharedSecret(priv, pub) {
        return this.modPow(pub, priv, this.p);
    }

    modPow(base, exponent, modulus) {
        if (modulus === 1) return 0;
        
        let result = 1;
        base = base % modulus;
        
        while (exponent > 0) {
            if (exponent & 1) {
                result = (result * base) % modulus;
            }
            exponent = exponent >> 1;
            base = (base * base) % modulus;
        }
        
        return result;
    }

    prime(num) {
        if (num < 2) return false;
        if (num === 2) return true;
        if ((num & 1) === 0) return false;
        
        const limit = Math.sqrt(num);
        for (let f = 3; f <= limit; f += 2) {
            if (num % f === 0) return false;
        }
        
        return true;
    }
}

module.exports = DiffieHellman;