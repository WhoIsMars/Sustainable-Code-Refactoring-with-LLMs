type fromType = { [key: number]: string[] };

type toType = { [s: string]: number };

export default (_old: fromType): toType => {
  const result: toType = {};
  for (const key in _old) {
    const points = Number(key);
    _old[key].forEach(letter => {
      result[letter.toLowerCase()] = points;
    });
  }
  return result;
};