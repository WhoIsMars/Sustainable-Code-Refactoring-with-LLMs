export default class {
  private static readonly letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  private static readonly usedNames = new Set<string>();

  public name: string = "";

  constructor() {
    if (!this.name) this.resetName();
  }

  resetName(): void {
    const generateRandomName = (): string => {
      const newRandomName = 
        `${this.randomLetters(2)}${this.randomDigits(3)}`;
      return !ClassName.usedNames.has(newRandomName)
        ? newRandomName
        : generateRandomName();
    };

    this.name = generateRandomName();
    ClassName.usedNames.add(this.name);
  }

  private randomLetters(length: number): string {
    return Array.from({ length }, () => 
      ClassName.letters.charAt(Math.floor(Math.random() * 26))
    ).join('');
  }

  private randomDigits(length: number): string {
    return Array.from({ length }, () => 
      Math.floor(Math.random() * 10).toString()
    ).join('');
  }
}