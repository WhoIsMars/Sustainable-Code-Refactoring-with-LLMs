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
    let newRandomName: string;
    
    do {
      newRandomName = this.generateRandomName();
    } while (this.usedNames.has(newRandomName));

    this.name = newRandomName;
    this.usedNames.add(newRandomName);
  }

  private generateRandomName(): string {
    let name = "";
    
    for (let i = 0; i < 2; i++) {
      name += NameGenerator.LETTERS[Math.floor(Math.random() * 26)];
    }
    
    for (let i = 0; i < 3; i++) {
      name += NameGenerator.DIGITS[Math.floor(Math.random() * 10)];
    }
    
    return name;
  }
}