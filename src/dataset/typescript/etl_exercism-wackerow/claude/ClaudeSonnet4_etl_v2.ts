type fromType = {[key: number]: string[]}

type toType = {[s: string]: number}

export default (_old: fromType): toType => {
  const result: toType = {}; 
  for (const points in _old) {
    const pointsNum = +points;
    const letters = _old[pointsNum];
    for (let i = 0; i < letters.length; i++) {
      result[letters[i].toLowerCase()] = pointsNum;
    }
  }
  return result;
}