const points: readonly number[] = [
  1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10
];

export default (word: string | undefined): number => {
  if (!word) return 0;
  
  let score = 0;
  for (let i = 0; i < word.length; i++) {
    const charCode = word.charCodeAt(i);
    if (charCode >= 65 && charCode <= 90) {
      score += points[charCode - 65];
    } else if (charCode >= 97 && charCode <= 122) {
      score += points[charCode - 97];
    }
  }
  return score;
}