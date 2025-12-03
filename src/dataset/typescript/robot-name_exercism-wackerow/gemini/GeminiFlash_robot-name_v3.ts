export default class {
  private static readonly LETTERS = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"];
  private static readonly MAX_RETRIES = 100;

  public name: string = "";
  private usedNames: Set<string> = new Set<string>();

  constructor() {
    if (!this.name) {
      this.resetName();
    }
  }

  resetName(): void {
    let newName: string | null = null;
    let retries = 0;

    while (newName === null && retries < Class.MAX_RETRIES) {
      const candidateName = this.generateRandomName();
      if (!this.usedNames.has(candidateName)) {
        newName = candidateName;
      }
      retries++;
    }

    if (newName === null) {
      console.warn("Failed to generate a unique name after multiple retries. Consider increasing MAX_RETRIES.");
      newName = this.generateFallbackName();
    }

    this.name = newName;
    this.usedNames.add(this.name);
  }

  private generateRandomName(): string {
    let newRandomName = "";
    for (let i = 0; i < 2; i++) {
      newRandomName += Class.LETTERS[Math.floor(Math.random() * Class.LETTERS.length)];
    }
    for (let i = 0; i < 3; i++) {
      newRandomName += Math.floor(Math.random() * 10).toString();
    }
    return newRandomName;
  }

  private generateFallbackName(): string {
    return 'FALLBACK_' + Date.now().toString();
  }
}