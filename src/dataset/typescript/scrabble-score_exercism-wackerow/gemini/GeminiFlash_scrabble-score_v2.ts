const points: { [s: string]: number } = {
  A: 1,
  B: 3,
  C: 3,
  D: 2,
  E: 1,
  F: 4,
  G: 2,
  H: 4,
  I: 1,
  J: 8,
  K: 5,
  L: 1,
  M: 3,
  N: 1,
  O: 1,
  P: 3,
  Q: 10,
  R: 1,
  S: 1,
  T: 1,
  U: 1,
  V: 4,
  W: 4,
  X: 8,
  Y: 4,
  Z: 10,
};

export default (word: string | undefined): number => {
  if (!word) {
    return 0;
  }

  let score = 0;
  const upperCaseWord = word.toUpperCase();
  const wordLength = upperCaseWord.length;

  for (let i = 0; i < wordLength; i++) {
    score += points[upperCaseWord[i]];
  }

  return score;
};