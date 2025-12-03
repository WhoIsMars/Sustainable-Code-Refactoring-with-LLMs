export default class {
  private readonly letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  public name: string = "";
  private usedNames = new Set<string>();

  constructor() {
    if (!this.name) this.resetName();
  }

  resetName(): void {
    const generateRandomName = (): string => {
      const randomLetters = Array.from({ length: 2 }, () =>
        this.letters.charAt(Math.floor(Math.random() * this.letters.length))
      ).join("");
      const randomNumbers = Math.floor(100 + Math.random() * 900).toString();
      const newRandomName = randomLetters + randomNumbers;

      return this.usedNames.has(newRandomName) ? generateRandomName() : newRandomName;
    };

    this.name = generateRandomName();
    this.usedNames.add(this.name);
  }
}