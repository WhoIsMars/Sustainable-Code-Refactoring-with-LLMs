export default class {
  constructor(private sentence: string) {}

  isPangram(): boolean {
    const alphabet = 'abcdefghijklmnopqrstuvwxyz';
    const lowerCaseSentence = this.sentence.toLowerCase();
    for (let i = 0; i < alphabet.length; i++) {
      if (!lowerCaseSentence.includes(alphabet[i])) {
        return false;
      }
    }
    return true;
  }
}