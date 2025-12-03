export default class Bob {
  hey(message: string): string {
    // Check for empty/whitespace-only message first (most common case)
    if (!/\S/.test(message)) {
      return 'Fine. Be that way!';
    }
    
    // Check if it's a question (ends with ?)
    const isQuestion = message.charCodeAt(message.length - 1) === 63; // ASCII code for '?'
    
    // Check if it's yelling (has uppercase letters and is all uppercase)
    let hasLetter = false;
    let isYelling = true;
    
    for (let i = 0; i < message.length; i++) {
      const char = message.charCodeAt(i);
      if ((char >= 65 && char <= 90) || (char >= 97 && char <= 122)) { // A-Z or a-z
        hasLetter = true;
        if (char >= 97 && char <= 122) { // lowercase letter found
          isYelling = false;
          break;
        }
      }
    }
    
    const isActuallyYelling = hasLetter && isYelling;
    
    if (isActuallyYelling && isQuestion) {
      return 'Calm down, I know what I\'m doing!';
    }
    
    if (isActuallyYelling) {
      return 'Whoa, chill out!';
    }
    
    if (isQuestion) {
      return 'Sure.';
    }
    
    return 'Whatever.';
  }
}