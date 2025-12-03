export default class ISBN {
  constructor(private _isbn: string) {}

  public isValid(): boolean {
    let checksum = 0;
    let digitCount = 0;
    let multiplier = 10;
    
    for (let i = 0; i < this._isbn.length && digitCount < 10; i++) {
      const char = this._isbn[i];
      
      if (char === '-') continue;
      
      if (digitCount === 9) {
        if (char === 'x' || char === 'X') {
          checksum += 10;
        } else if (char >= '0' && char <= '9') {
          checksum += (char.charCodeAt(0) - 48);
        } else {
          return false;
        }
      } else {
        if (char >= '0' && char <= '9') {
          checksum += (char.charCodeAt(0) - 48) * multiplier;
          multiplier--;
        } else {
          return false;
        }
      }
      
      digitCount++;
    }
    
    return digitCount === 10 && checksum % 11 === 0;
  }
}