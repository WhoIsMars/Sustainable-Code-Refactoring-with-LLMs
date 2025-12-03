export const parse = phrase => {
  let acronym = "";
  for (const word of phrase.toUpperCase().split(/[^A-Z']+/)) {
    if (word) {
      acronym += word[0];
    }
  }
  return acronym;
};