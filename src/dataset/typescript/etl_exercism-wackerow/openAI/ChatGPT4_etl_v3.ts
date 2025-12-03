type fromType = { [key: number]: string[] };

type toType = { [s: string]: number };

export default (_old: fromType): toType => {
  const result: toType = {};
  for (const points in _old) {
    const score = Number(points);
    _old[score].forEach(letter => {
      result[letter.toLowerCase()] = score;
    });
  }
  return result;
};