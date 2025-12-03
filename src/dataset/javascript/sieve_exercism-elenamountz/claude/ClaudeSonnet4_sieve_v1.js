export default class Sieve{
  constructor(number){
    this.number = number;
    this.list = Array.from(Array(this.number - 1), (value, index) => index+2);
    this.primes = this.findPrimes();
  }
  findPrimes(){
    const isPrime = new Array(this.number + 1).fill(true);
    isPrime[0] = isPrime[1] = false;

    for(let i = 2; i * i <= this.number; i++){
      if(isPrime[i]){
        for(let j = i * i; j <= this.number; j += i){
          isPrime[j] = false;
        }
      }
    }

    const primes = [];
    for(let i = 2; i <= this.number; i++){
      if(isPrime[i]){
        primes.push(i);
      }
    }
    return primes;
  }
}