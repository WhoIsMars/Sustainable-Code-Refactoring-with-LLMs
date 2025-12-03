#include "raindrops.h"
#include <stdio.h>

char *convert(char result[], int drops) {
  result[0] = '\0';
  int len = 0;

  if (drops % 3 == 0) {
    result[len++] = 'P';
    result[len++] = 'l';
    result[len++] = 'i';
    result[len++] = 'n';
    result[len++] = 'g';
  }
  if (drops % 5 == 0) {
    result[len++] = 'P';
    result[len++] = 'l';
    result[len++] = 'a';
    result[len++] = 'n';
    result[len++] = 'g';
  }
  if (drops % 7 == 0) {
    result[len++] = 'P';
    result[len++] = 'l';
    result[len++] = 'o';
    result[len++] = 'n';
    result[len++] = 'g';
  }

  if (len == 0) {
    sprintf(result, "%d", drops);
  } else {
    result[len] = '\0';
  }

  return result;
}