export default class Raindrops {
  public convert(num: number): string {
    const sounds = [
      { factor: 3, sound: 'Pling' },
      { factor: 5, sound: 'Plang' },
      { factor: 7, sound: 'Plong' },
    ];
    let raindrop = sounds.reduce((acc, { factor, sound }) => 
      num % factor === 0 ? acc + sound : acc, 
      ''
    );
    return raindrop || num.toString();
  }
}