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
  size_t output_size = 16;
  char *output = (char *)malloc(output_size * sizeof(char));
  if (output == NULL) {
    return NULL;
  }
  output[0] = '\0';
  size_t output_len = 0;

  for (int i = 0; i < 13; i++) {
    while (number >= arabicToRomanMap[i].arabic) {
      size_t roman_len = strlen(arabicToRomanMap[i].roman);
      if (output_len + roman_len >= output_size - 1) {
        output_size *= 2;
        char *temp = (char *)realloc(output, output_size * sizeof(char));
        if (temp == NULL) {
          free(output);
          return NULL;
        }
        output = temp;
      }
      strcpy(output + output_len, arabicToRomanMap[i].roman);
      output_len += roman_len;
      number -= arabicToRomanMap[i].arabic;
    }
  }

  return output;
}