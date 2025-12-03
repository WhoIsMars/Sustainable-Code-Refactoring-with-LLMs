export default class {
  private readonly sentence: string;

  constructor(sentence: string) {
    this.sentence = sentence.toLowerCase();
  }

  isPangram(): boolean {
    const alphabet = 'abcdefghijklmnopqrstuvwxyz';
    for (let i = 0; i < alphabet.length; i++) {
      if (!this.sentence.includes(alphabet[i])) {
        return false;
      }
    }
    return true;
  }
}