var Sieve = function(limit) {
  this.primes = [];
  const isPrime = new Array(limit + 1).fill(true);
  isPrime[0] = isPrime[1] = false;

  for (let number = 2; number <= Math.sqrt(limit); number++) {
    if (isPrime[number]) {
      for (let multiple = number * number; multiple <= limit; multiple += number) {
        isPrime[multiple] = false;
      }
    }
  }

  for (let number = 2; number <= limit; number++) {
    if (isPrime[number]) {
      this.primes.push(number);
    }
  }
};

module.exports = Sieve;