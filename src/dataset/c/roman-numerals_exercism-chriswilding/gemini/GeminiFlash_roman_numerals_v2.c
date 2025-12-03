#include "roman_numerals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int arabic;
  char *roman;
  int roman_len;
} ArabicToRoman;

ArabicToRoman arabicToRomanMap[] = {
    {1000, "M", 1}, {900, "CM", 2}, {500, "D", 1}, {400, "CD", 2}, {100, "C", 1},
    {90, "XC", 2},  {50, "L", 1},   {40, "XL", 2}, {10, "X", 1},   {9, "IX", 2},
    {5, "V", 1},    {4, "IV", 2},   {1, "I", 1}
};

char *to_roman_numeral(unsigned int number) {
  char *output = (char *)malloc(16 * sizeof(char));
  if (output == NULL) return NULL; // Handle allocation failure

  int output_index = 0;

  for (int i = 0; i < 13; i++) {
    ArabicToRoman arabicToRoman = arabicToRomanMap[i];
    while (number >= arabicToRoman.arabic) {
      memcpy(output + output_index, arabicToRoman.roman, arabicToRoman.roman_len);
      output_index += arabicToRoman.roman_len;
      number -= arabicToRoman.arabic;
    }
  }

  output[output_index] = '\0';
  return output;
}