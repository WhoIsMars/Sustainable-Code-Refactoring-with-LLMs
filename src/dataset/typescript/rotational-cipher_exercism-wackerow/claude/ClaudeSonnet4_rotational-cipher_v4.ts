export default class RotationalCipher {
  private static readonly _abc = 'abcdefghijklmnopqrstuvwxyz'
  private static readonly _ABC = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'

  public static rotate(message: string, key: number): string {
    const normalizedKey = ((key % 26) + 26) % 26
    if (normalizedKey === 0) return message
    
    const result: string[] = new Array(message.length)
    
    for (let i = 0; i < message.length; i++) {
      const char = message[i]
      const code = char.charCodeAt(0)
      
      if (code >= 97 && code <= 122) {
        result[i] = String.fromCharCode(((code - 97 + normalizedKey) % 26) + 97)
      } else if (code >= 65 && code <= 90) {
        result[i] = String.fromCharCode(((code - 65 + normalizedKey) % 26) + 65)
      } else {
        result[i] = char
      }
    }
    
    return result.join('')
  }
}