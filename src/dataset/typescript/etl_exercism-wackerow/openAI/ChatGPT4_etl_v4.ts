type fromType = { [key: number]: string[] };

type toType = { [s: string]: number };

export default (_old: fromType): toType => {
  const result: toType = {};
  for (const points in _old) {
    const pointValue = Number(points);
    _old[pointValue].forEach(letter => {
      result[letter.toLowerCase()] = pointValue;
    });
  }
  return result;
};