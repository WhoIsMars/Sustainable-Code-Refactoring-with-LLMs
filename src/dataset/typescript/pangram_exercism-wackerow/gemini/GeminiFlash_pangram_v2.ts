export default class {
  private readonly lowerCaseSentence: string;

  constructor(sentence: string) {
    this.lowerCaseSentence = sentence.toLowerCase();
  }

  isPangram(): boolean {
    const alphabet = 'abcdefghijklmnopqrstuvwxyz';
    for (let i = 0; i < alphabet.length; i++) {
      if (!this.lowerCaseSentence.includes(alphabet[i])) {
        return false;
      }
    }
    return true;
  }
}