type fromType = {[key: number]: string[]}

type toType = {[s: string]: number}

export default (_old: fromType): toType => {
  const result: toType = {};
  for (const pointsStr in _old) {
    if (_old.hasOwnProperty(pointsStr)) {
      const points = parseInt(pointsStr, 10);
      const letters = _old[pointsStr];
      if (letters) {
        for (let i = 0; i < letters.length; i++) {
          const letter = letters[i];
          result[letter.toLowerCase()] = points;
        }
      }
    }
  }
  return result;
}