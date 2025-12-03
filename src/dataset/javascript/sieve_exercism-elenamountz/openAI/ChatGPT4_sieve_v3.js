export default class Sieve {
  constructor(number) {
    this.number = number;
    this.list = Array.from({ length: this.number - 1 }, (_, index) => index + 2);
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

    return this.list.filter((element) => isPrime[element]);
  }
}