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
    let newRandomName: string | null = null;
    let retries = 0;

    while (newRandomName === null && retries < Class.MAX_RETRIES) {
      let tempName = "";
      for (let i = 0; i < 2; i++) {
        tempName += Class.LETTERS[Math.floor(Math.random() * Class.LETTERS.length)];
      }
      for (let i = 0; i < 3; i++) {
        tempName += Math.floor(Math.random() * 10).toString();
      }

      if (!this.usedNames.has(tempName)) {
        newRandomName = tempName;
      }
      retries++;
    }

    if (newRandomName === null) {
      throw new Error("Failed to generate a unique name after maximum retries.");
    }

    this.name = newRandomName;
    this.usedNames.add(this.name);
  }
}