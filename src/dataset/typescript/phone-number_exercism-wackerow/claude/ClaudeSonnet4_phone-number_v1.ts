export default class PhoneNumber {
  private _sanitized: string | undefined;
  private _processed = false;

  constructor(private _input: string) {}

  public number(): string | undefined {
    if (!this._processed) {
      this._processed = true;
      
      // Single pass sanitization with early exit
      let sanitized = '';
      for (let i = 0; i < this._input.length; i++) {
        const char = this._input[i];
        if ((char >= '0' && char <= '9') || (char >= 'a' && char <= 'z') || (char >= 'A' && char <= 'Z')) {
          sanitized += char;
        }
      }
      
      // Handle 11-digit numbers starting with '1'
      if (sanitized.length === 11 && sanitized[0] === '1') {
        sanitized = sanitized.slice(1);
      }
      
      // Validate format inline without regex
      if (sanitized.length === 10 &&
          sanitized[0] >= '2' && sanitized[0] <= '9' &&
          sanitized[3] >= '2' && sanitized[3] <= '9') {
        
        // Check remaining digits are numeric
        let isValid = true;
        for (let i = 1; i < 10; i++) {
          if (i === 3) continue; // Already checked
          if (sanitized[i] < '0' || sanitized[i] > '9') {
            isValid = false;
            break;
          }
        }
        
        this._sanitized = isValid ? sanitized : undefined;
      } else {
        this._sanitized = undefined;
      }
    }
    
    return this._sanitized;
  }
}