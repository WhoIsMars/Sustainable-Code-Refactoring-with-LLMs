export default class Beer {
  constructor() {}

  static verse(n) {
    const bottleWord = n === 1 ? 'bottle' : 'bottles';
    const nextBottleWord = n === 2 ? 'bottle' : 'bottles';
    const nextCount = n === 1 ? 'no more' : String(n - 1);
    
    switch (n) {
      case 0:
        return 'No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n';
      case 1:
        return '1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n';
      default:
        return `${n} ${bottleWord} of beer on the wall, ${n} ${bottleWord} of beer.\nTake one down and pass it around, ${nextCount} ${nextBottleWord} on the wall.\n`;
    }
  }

  static sing(from = 99, to = 0) {
    const verses = [];
    for (let i = from; i >= to; i--) {
      verses.push(this.verse(i));
    }
    return verses.join('\n').slice(0, -1);
  }
}