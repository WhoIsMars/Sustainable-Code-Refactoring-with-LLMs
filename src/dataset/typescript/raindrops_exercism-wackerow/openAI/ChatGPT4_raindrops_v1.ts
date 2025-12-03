export default class Raindrops {
  public convert(num: number): string {
    const factors = [
      { divisor: 3, sound: 'Pling' },
      { divisor: 5, sound: 'Plang' },
      { divisor: 7, sound: 'Plong' },
    ];

    let raindrop = factors.reduce((acc, { divisor, sound }) => 
      num % divisor === 0 ? acc + sound : acc, '');

    return raindrop || num.toString();
  }
}