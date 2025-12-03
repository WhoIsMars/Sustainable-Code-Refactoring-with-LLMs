export default class {
  private static readonly letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  private static readonly lettersLength = 26;

  public name: string = "";
  private usedNames: Set<string> = new Set();

  constructor() {
    if (!this.name) this.resetName();
  }

  resetName(): void {
    let newRandomName: string;
    
    do {
      newRandomName = 
        this.letters[Math.floor(Math.random() * 26)] +
        this.letters[Math.floor(Math.random() * 26)] +
        Math.floor(Math.random() * 10) +
        Math.floor(Math.random() * 10) +
        Math.floor(Math.random() * 10);
    } while (this.usedNames.has(newRandomName));

    this.name = newRandomName;
    this.usedNames.add(newRandomName);
  }
}