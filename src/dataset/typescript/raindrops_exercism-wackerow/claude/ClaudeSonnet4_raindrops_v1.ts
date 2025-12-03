export default class Raindrops {
  public convert(num: number): string {
    const divisibleBy3 = num % 3 === 0;
    const divisibleBy5 = num % 5 === 0;
    const divisibleBy7 = num % 7 === 0;
    
    if (!divisibleBy3 && !divisibleBy5 && !divisibleBy7) {
      return num.toString();
    }
    
    let raindrop = '';
    if (divisibleBy3) raindrop += 'Pling';
    if (divisibleBy5) raindrop += 'Plang';
    if (divisibleBy7) raindrop += 'Plong';
    
    return raindrop;
  }
}