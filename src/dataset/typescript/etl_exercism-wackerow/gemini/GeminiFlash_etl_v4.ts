type fromType = {[key: number]: string[]}

type toType = {[s: string]: number}

export default (_old: fromType): toType => {
  const result: toType = {};
  for (const pointsStr in _old) {
    if (_old.hasOwnProperty(pointsStr)) {
      const points = parseInt(pointsStr);
      const letters = _old[pointsStr];
      const len = letters.length;
      for (let i = 0; i < len; i++) {
        const letter = letters[i];
        result[letter.toLowerCase()] = points;
      }
    }
  }
  return result;
}