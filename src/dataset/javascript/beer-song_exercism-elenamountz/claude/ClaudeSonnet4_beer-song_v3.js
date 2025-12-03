export default class Beer {
  constructor() {}

  static verse(n) {
    const bottleWord = n === 1 ? 'bottle' : 'bottles';
    
    if (n === 0) {
      return 'No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n';
    }
    
    if (n === 1) {
      return '1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n';
    }
    
    const nextBottleWord = n === 2 ? 'bottle' : 'bottles';
    return `${n} ${bottleWord} of beer on the wall, ${n} ${bottleWord} of beer.\nTake one down and pass it around, ${n - 1} ${nextBottleWord} of beer on the wall.\n`;
  }

  static sing(from = 99, to = 0) {
    const verses = [];
    for (let i = from; i >= to; i--) {
      verses.push(this.verse(i));
    }
    return verses.join('\n').slice(0, -1);
  }
}