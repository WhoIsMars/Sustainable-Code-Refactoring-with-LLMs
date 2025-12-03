#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t resistor_band[]) {
  resistor_value_t resistor_value;

  resistor_value.value = (resistor_band[0] * 10 + resistor_band[1]);

  // Optimized power of 10 calculation using a lookup table
  static const uint32_t multipliers[] = {1, 10, 100, 1000, 10000, 100000,
                                          1000000, 10000000, 100000000, 1000000000};
  resistor_value.value *= multipliers[resistor_band[2]];

  if (resistor_value.value >= 1000) {
    resistor_value.value /= 1000;
    resistor_value.unit = KILOOHMS;
  } else {
    resistor_value.unit = OHMS;
  }

  return resistor_value;
}