export default class Sieve {
  constructor(number) {
    this.number = number;
    this.primes = this.findPrimes();
  }

  findPrimes() {
    const limit = Math.sqrt(this.number);
    const isComposite = new Array(this.number + 1);

    for (let i = 2; i <= limit; i++) {
      if (!isComposite[i]) {
        for (let j = i * i; j <= this.number; j += i) {
          isComposite[j] = true;
        }
      }
    }

    const primes = [];
    for (let i = 2; i <= this.number; i++) {
      if (!isComposite[i]) {
        primes.push(i);
      }
    }
    return primes;
  }
}