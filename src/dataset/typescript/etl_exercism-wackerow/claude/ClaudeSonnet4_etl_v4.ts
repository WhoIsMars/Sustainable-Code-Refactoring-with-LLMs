type fromType = {[key: number]: string[]}

type toType = {[s: string]: number}

export default (_old: fromType): toType => {
  const result: toType = {};
  const keys = Object.keys(_old);
  
  for (let i = 0; i < keys.length; i++) {
    const points = +keys[i];
    const letters = _old[points];
    
    for (let j = 0; j < letters.length; j++) {
      result[letters[j].toLowerCase()] = points;
    }
  }
  
  return result;
}