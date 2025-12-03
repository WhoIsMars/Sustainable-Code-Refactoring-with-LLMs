export default class {
  private static readonly LETTERS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  
  public name: string = "";
  private usedNames = new Set<string>();

  constructor() {
    this.resetName();
  }

  resetName(): void {
    let newRandomName: string;
    
    do {
      newRandomName = 
        this.LETTERS[Math.floor(Math.random() * 26)] +
        this.LETTERS[Math.floor(Math.random() * 26)] +
        Math.floor(Math.random() * 10) +
        Math.floor(Math.random() * 10) +
        Math.floor(Math.random() * 10);
    } while (this.usedNames.has(newRandomName));

    this.name = newRandomName;
    this.usedNames.add(newRandomName);
  }
}