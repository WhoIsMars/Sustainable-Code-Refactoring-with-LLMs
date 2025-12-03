export default class {
  private static readonly letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  private static readonly usedNames = new Set<string>();

  public name: string;

  constructor() {
    this.name = this.generateUniqueName();
  }

  resetName(): void {
    this.name = this.generateUniqueName();
  }

  private generateUniqueName(): string {
    let newRandomName: string;
    do {
      newRandomName = this.generateRandomName();
    } while (exportedClass.usedNames.has(newRandomName));
    exportedClass.usedNames.add(newRandomName);
    return newRandomName;
  }

  private generateRandomName(): string {
    const lettersPart = Array.from({ length: 2 }, () =>
      exportedClass.letters.charAt(Math.floor(Math.random() * exportedClass.letters.length))
    ).join("");
    const numbersPart = Math.floor(100 + Math.random() * 900).toString();
    return lettersPart + numbersPart;
  }
}