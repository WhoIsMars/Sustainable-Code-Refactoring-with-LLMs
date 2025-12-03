export default class {
  private static readonly letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  private static readonly letterCount = 26;
  private static readonly usedNames = new Set<string>();

  public name: string = "";

  constructor() {
    if (!this.name) this.resetName();
  }

  resetName(): void {
    const generateRandomName = (): string => {
      const randomLetters = Array.from({ length: 2 }, () =>
        String.fromCharCode(65 + Math.floor(Math.random() * 26))
      ).join("");
      const randomNumbers = Math.floor(Math.random() * 1000)
        .toString()
        .padStart(3, "0");
      const newRandomName = randomLetters + randomNumbers;

      if (this.constructor["usedNames"].has(newRandomName)) {
        return generateRandomName();
      }
      return newRandomName;
    };

    this.name = generateRandomName();
    this.constructor["usedNames"].add(this.name);
  }
}