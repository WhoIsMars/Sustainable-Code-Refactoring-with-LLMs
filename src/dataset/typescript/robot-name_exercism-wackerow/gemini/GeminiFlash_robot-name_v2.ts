export default class {
  private static readonly letters = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
  private static readonly maxNameAttempts = 100;

  public name: string = "";
  private usedNames: string[] = [];

  constructor() {
    if (!this.name) {
      this.resetName();
    }
  }

  resetName(): void {
    let attempts = 0;
    while (attempts < NameGenerator.maxNameAttempts) {
      let newRandomName = "";
      for (let i = 0; i < 2; i++) {
        newRandomName += NameGenerator.letters[Math.floor(Math.random() * NameGenerator.letters.length)];
      }
      for (let i = 0; i < 3; i++) {
        newRandomName += Math.floor(Math.random() * 10).toString();
      }

      if (this.usedNames.indexOf(newRandomName) === -1) {
        this.name = newRandomName;
        this.usedNames.push(this.name);
        return;
      }
      attempts++;
    }

    // Fallback: If after max attempts, still no unique name, generate a truly unique name
    this.name = this.generateGuaranteedUniqueName();
    this.usedNames.push(this.name);
  }

  private generateGuaranteedUniqueName(): string {
    let baseName = "ZZ999";
    let uniqueSuffix = this.usedNames.length.toString();
    return baseName + uniqueSuffix;
  }
}