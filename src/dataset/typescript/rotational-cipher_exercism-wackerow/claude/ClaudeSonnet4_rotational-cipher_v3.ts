export default class RotationalCipher {
  private static readonly _LOWER_A = 97
  private static readonly _UPPER_A = 65
  private static readonly _ALPHABET_SIZE = 26

  public static rotate(message: string, key: number): string {
    const normalizedKey = ((key % this._ALPHABET_SIZE) + this._ALPHABET_SIZE) % this._ALPHABET_SIZE
    let encrypted = ''
    
    for (let i = 0; i < message.length; i++) {
      const charCode = message.charCodeAt(i)
      
      if (charCode >= this._LOWER_A && charCode <= this._LOWER_A + 25) {
        encrypted += String.fromCharCode(((charCode - this._LOWER_A + normalizedKey) % this._ALPHABET_SIZE) + this._LOWER_A)
      } else if (charCode >= this._UPPER_A && charCode <= this._UPPER_A + 25) {
        encrypted += String.fromCharCode(((charCode - this._UPPER_A + normalizedKey) % this._ALPHABET_SIZE) + this._UPPER_A)
      } else {
        encrypted += message[i]
      }
    }
    
    return encrypted
  }
}