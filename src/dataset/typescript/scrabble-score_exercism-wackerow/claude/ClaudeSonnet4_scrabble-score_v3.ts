const points: ReadonlyArray<number> = [
  1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
];

export default (word: string | undefined): number => {
  if (!word) return 0;
  
  let score = 0;
  for (let i = 0; i < word.length; i++) {
    const charCode = word.charCodeAt(i);
    const index = charCode >= 97 ? charCode - 97 : charCode - 65;
    if (index >= 0 && index < 26) {
      score += points[index];
    }
  }
  return score;
}