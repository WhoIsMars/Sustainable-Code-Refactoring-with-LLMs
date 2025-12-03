export default class Raindrops {
  public convert(num: number): string {
    const mappings = [
      [3, 'Pling'],
      [5, 'Plang'],
      [7, 'Plong']
    ] as const;

    let raindrop = mappings.reduce((acc, [factor, sound]) => 
      num % factor === 0 ? acc + sound : acc, '');

    return raindrop || num.toString();
  }
}