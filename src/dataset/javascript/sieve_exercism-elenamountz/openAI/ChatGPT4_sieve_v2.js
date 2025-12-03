export default class Sieve {
  constructor(number) {
    this.number = number;
    this.primes = this.findPrimes();
  }

  findPrimes() {
    const isPrime = Array(this.number + 1).fill(true);
    isPrime[0] = isPrime[1] = false;

    for (let i = 2; i * i <= this.number; i++) {
      if (isPrime[i]) {
        for (let j = i * i; j <= this.number; j += i) {
          isPrime[j] = false;
        }
      }
    }

    return isPrime.reduce((primes, isPrime, index) => {
      if (isPrime) primes.push(index);
      return primes;
    }, []);
  }
}