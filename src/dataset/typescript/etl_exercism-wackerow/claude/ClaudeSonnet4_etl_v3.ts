type fromType = {[key: number]: string[]}

type toType = {[s: string]: number}

export default (_old: fromType): toType => {
  const result: toType = {};
  const entries = Object.entries(_old);
  
  for (let i = 0; i < entries.length; i++) {
    const [points, letters] = entries[i];
    const pointsNum = +points;
    
    for (let j = 0; j < letters.length; j++) {
      const letter = letters[j];
      if (letter.length === 1) {
        const lowerLetter = letter >= 'A' && letter <= 'Z' 
          ? String.fromCharCode(letter.charCodeAt(0) + 32)
          : letter;
        result[lowerLetter] = pointsNum;
      } else {
        result[letter.toLowerCase()] = pointsNum;
      }
    }
  }
  
  return result;
}