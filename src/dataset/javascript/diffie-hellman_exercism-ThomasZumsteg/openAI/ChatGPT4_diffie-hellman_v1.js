class DiffieHellman {
    constructor(p, g) {
        if (!(1 <= p && p < 9999) || !(1 <= g && g < 9999) || !DiffieHellman.isPrime(p) || !DiffieHellman.isPrime(g)) {
            throw new Error("Arguments are out of range or not prime");
        }
        this.p = p;
        this.g = g;
    }

    getPublicKeyFromPrivateKey(a) {
        if (!(2 <= a && a < this.p)) throw new Error("Not a valid private key");
        return this.modExp(this.g, a, this.p);
    }

    getSharedSecret(priv, pub) {
        return this.modExp(pub, priv, this.p);
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

    modExp(base, exp, mod) {
        let result = 1;
        base = base % mod;
        while (exp > 0) {
            if (exp % 2 === 1) result = (result * base) % mod;
            exp = Math.floor(exp / 2);
            base = (base * base) % mod;
        }
        return result;
    }
}

module.exports = DiffieHellman;