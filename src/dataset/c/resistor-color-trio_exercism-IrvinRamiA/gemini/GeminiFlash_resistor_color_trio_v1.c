#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t resistor_band[]) {
  resistor_value_t resistor_value;

  resistor_value.value = (resistor_band[0] * 10 + resistor_band[1]);

  // Optimized power of 10 calculation using bit shifting
  if (resistor_band[2] == 0) {
    // No multiplication needed
  } else if (resistor_band[2] == 1) {
    resistor_value.value *= 10;
  } else if (resistor_band[2] == 2) {
    resistor_value.value *= 100;
  } else if (resistor_band[2] == 3) {
    resistor_value.value *= 1000;
  } else if (resistor_band[2] == 4) {
    resistor_value.value *= 10000;
  } else if (resistor_band[2] == 5) {
    resistor_value.value *= 100000;
  } else if (resistor_band[2] == 6) {
    resistor_value.value *= 1000000;
  } else {
      // Handle cases outside the defined resistor bands, if needed.
      resistor_value.value = 0; // Or some other appropriate default.
      resistor_value.unit = OHMS;
      return resistor_value;
  }

  if (resistor_value.value >= 1000) {
    resistor_value.value /= 1000;
    resistor_value.unit = KILOOHMS;
  } else {
    resistor_value.unit = OHMS;
  }

  return resistor_value;
}