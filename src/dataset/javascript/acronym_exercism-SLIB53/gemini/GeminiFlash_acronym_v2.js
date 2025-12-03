export const parse = phrase => {
  let acronym = "";
  const words = phrase.toUpperCase().split(/[^A-Z']+/);

  for (const word of words) {
    if (word) {
      acronym += word[0];
    }
  }
  return acronym;
};