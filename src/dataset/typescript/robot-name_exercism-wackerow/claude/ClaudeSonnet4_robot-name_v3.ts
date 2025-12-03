export default class {
  private static readonly LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  private static readonly DIGITS = "0123456789";

  public name: string = "";
  private usedNames: Set<string> = new Set();

  constructor() {
    if (!this.name) {
      this.resetName();
    }
  }

  resetName(): void {
    const generateRandomName = (): string => {
      const chars = new Array(5);
      
      for (let i = 0; i < 2; i++) {
        chars[i] = NameGenerator.LETTERS[Math.floor(Math.random() * 26)];
      }
      
      for (let i = 2; i < 5; i++) {
        chars[i] = NameGenerator.DIGITS[Math.floor(Math.random() * 10)];
      }
      
      const newRandomName = chars.join('');
      
      if (this.usedNames.has(newRandomName)) {
        return generateRandomName();
      }
      
      return newRandomName;
    };

    this.name = generateRandomName();
    this.usedNames.add(this.name);
  }
}