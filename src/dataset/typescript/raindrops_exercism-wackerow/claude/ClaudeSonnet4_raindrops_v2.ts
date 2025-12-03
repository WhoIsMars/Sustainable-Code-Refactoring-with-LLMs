export default class Raindrops {
  public convert(num: number): string {
    let raindrop = '';
    
    if (num % 3 === 0) raindrop += 'Pling';
    if (num % 5 === 0) raindrop += 'Plang';
    if (num % 7 === 0) raindrop += 'Plong';
    
    return raindrop || num.toString();
  }
}