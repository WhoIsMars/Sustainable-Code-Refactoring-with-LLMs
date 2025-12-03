export default class Raindrops {
  public convert(num: number): string {
    const isDivisibleBy3 = num % 3 === 0;
    const isDivisibleBy5 = num % 5 === 0;
    const isDivisibleBy7 = num % 7 === 0;
    
    if (!isDivisibleBy3 && !isDivisibleBy5 && !isDivisibleBy7) {
      return num.toString();
    }
    
    let raindrop = '';
    if (isDivisibleBy3) raindrop += 'Pling';
    if (isDivisibleBy5) raindrop += 'Plang';
    if (isDivisibleBy7) raindrop += 'Plong';
    
    return raindrop;
  }
}