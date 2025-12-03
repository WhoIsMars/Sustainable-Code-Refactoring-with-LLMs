export default class Isogram {
  public static isIsogram(input: string): boolean {
    const normalized = input.toLowerCase();
    const letters = new Set<string>();

    for (let i = 0; i < normalized.length; i++) {
      const char = normalized[i];
      if (char >= 'a' && char <= 'z') {
        if (letters.has(char)) {
          return false;
        }
        letters.add(char);
      }
    }

    return true;
  }
}