#include "roman_numerals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int arabic;
  const char *roman;
} ArabicToRoman;

static const ArabicToRoman arabicToRomanMap[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
    {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
    {5, "V"},    {4, "IV"},   {1, "I"},
};

char *to_roman_numeral(unsigned int number) {
  static char output[20];
  size_t pos = 0;

  for (int i = 0; i < 13 && number > 0; i++) {
    while (number >= arabicToRomanMap[i].arabic) {
      size_t len = strlen(arabicToRomanMap[i].roman);
      memcpy(output + pos, arabicToRomanMap[i].roman, len);
      pos += len;
      number -= arabicToRomanMap[i].arabic;
    }
  }

  output[pos] = '\0';
  return strdup(output);
}