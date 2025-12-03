export default class Beer {
  constructor() {}

  static verse(n) {
    switch (n) {
      case 0:
        return "No more bottles of beer on the wall, no more bottles of beer.\nGo to the store and buy some more, 99 bottles of beer on the wall.\n";
      case 1:
        return "1 bottle of beer on the wall, 1 bottle of beer.\nTake it down and pass it around, no more bottles of beer on the wall.\n";
      case 2:
        return "2 bottles of beer on the wall, 2 bottles of beer.\nTake one down and pass it around, 1 bottle of beer on the wall.\n";
      default:
        return `${n} bottles of beer on the wall, ${n} bottles of beer.\nTake one down and pass it around, ${n - 1} bottles of beer on the wall.\n`;
    }
  }

  static sing(from = 99, to = 0) {
    let result = "";
    for (let i = from; i >= to; i--) {
      result += Beer.verse(i) + "\n";
    }
    return result.slice(0, -1);
  }
}