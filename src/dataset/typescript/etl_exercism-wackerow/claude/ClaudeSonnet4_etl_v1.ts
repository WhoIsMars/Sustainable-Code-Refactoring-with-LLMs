type fromType = {[key: number]: string[]}

type toType = {[s: string]: number}

export default (_old: fromType): toType => {
  const result: toType = {}; 
  for (const pointsStr in _old) {
    const points = +pointsStr;
    const letters = _old[pointsStr];
    for (let i = 0; i < letters.length; i++) {
      result[letters[i].toLowerCase()] = points;
    }
  }
  return result;
}