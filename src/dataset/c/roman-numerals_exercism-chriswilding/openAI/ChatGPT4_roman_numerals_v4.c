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
  char *output = (char *)malloc(16);
  if (!output) return NULL;
  size_t pos = 0;

  for (size_t i = 0; i < sizeof(arabicToRomanMap) / sizeof(ArabicToRoman); i++) {
    while (number >= arabicToRomanMap[i].arabic) {
      size_t len = strlen(arabicToRomanMap[i].roman);
      memcpy(output + pos, arabicToRomanMap[i].roman, len);
      pos += len;
      number -= arabicToRomanMap[i].arabic;
    }
  }

  output[pos] = '\0';
  return output;
}