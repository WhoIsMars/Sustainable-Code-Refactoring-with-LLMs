export default class RotationalCipher {
  private static readonly _aCode = 97; // 'a'.charCodeAt(0)
  private static readonly _ACode = 65; // 'A'.charCodeAt(0)
  private static readonly _alphabetSize = 26;

  public static rotate(message: string, key: number): string {
    const normalizedKey = ((key % this._alphabetSize) + this._alphabetSize) % this._alphabetSize;
    let encrypted = '';
    
    for (let i = 0; i < message.length; i++) {
      const charCode = message.charCodeAt(i);
      
      if (charCode >= this._aCode && charCode <= this._aCode + 25) {
        encrypted += String.fromCharCode(this._aCode + (charCode - this._aCode + normalizedKey) % this._alphabetSize);
      } else if (charCode >= this._ACode && charCode <= this._ACode + 25) {
        encrypted += String.fromCharCode(this._ACode + (charCode - this._ACode + normalizedKey) % this._alphabetSize);
      } else {
        encrypted += message[i];
      }
    }
    
    return encrypted;
  }
}