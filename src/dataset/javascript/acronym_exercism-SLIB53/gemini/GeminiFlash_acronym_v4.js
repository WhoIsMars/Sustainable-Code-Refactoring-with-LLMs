export const parse = phrase => {
  let acronym = "";
  const words = phrase.toUpperCase().split(/[^A-Z']+/);

  for (let i = 0; i < words.length; i++) {
    const word = words[i];
    if (word.length > 0) {
      acronym += word[0];
    }
  }

  return acronym;
};