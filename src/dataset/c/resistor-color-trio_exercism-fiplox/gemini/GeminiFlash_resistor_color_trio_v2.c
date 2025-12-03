#include "resistor_color_trio.h"

resistor_value_t color_code(const resistor_band_t colors[]) {
  resistor_value_t res;

  res.value = (colors[0] * 10 + colors[1]);

  if (colors[2] == 0) {
    // No multiplier needed
  } else if (colors[2] == 1) {
    res.value *= 10;
  } else if (colors[2] == 2) {
    res.value *= 100;
  } else if (colors[2] == 3) {
    res.value *= 1000;
  } else if (colors[2] == 4) {
    res.value *= 10000;
  } else if (colors[2] == 5) {
    res.value *= 100000;
  } else if (colors[2] == 6) {
    res.value *= 1000000;
  } else if (colors[2] == 7) {
    res.value *= 10000000;
  } else if (colors[2] == 8) {
    res.value *= 100000000;
  } else if (colors[2] == 9) {
    res.value *= 1000000000;
  }

  res.unit = OHMS;

  if (res.value >= 1000 && (res.value % 1000) == 0) {
    res.unit = KILOOHMS;
    res.value /= 1000;
  }

  return res;
}