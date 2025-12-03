export default class Raindrops {
  public convert(num: number): string {
    const div3 = num % 3 === 0;
    const div5 = num % 5 === 0;
    const div7 = num % 7 === 0;
    
    if (!div3 && !div5 && !div7) {
      return num.toString();
    }
    
    return (div3 ? 'Pling' : '') + (div5 ? 'Plang' : '') + (div7 ? 'Plong' : '');
  }
}