var Sieve = function(size) {
    this.primes = [];
    
    if (size < 2) return;
    
    var sieve = new Array(size + 1);
    sieve.fill(true);
    sieve[0] = sieve[1] = false;
    
    this.primes.push(2);
    
    for (var n = 3; n * n <= size; n += 2) {
        if (sieve[n]) {
            for (var m = n * n; m <= size; m += 2 * n) {
                sieve[m] = false;
            }
        }
    }
    
    for (var i = 3; i <= size; i += 2) {
        if (sieve[i]) {
            this.primes.push(i);
        }
    }
}

module.exports = Sieve;