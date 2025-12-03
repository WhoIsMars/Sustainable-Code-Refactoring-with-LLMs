#include "resistor_color_trio.h"

resistor_value_t color_code(resistor_band_t resistor_band[]) {
  resistor_value_t resistor_value;
  uint32_t value = (resistor_band[0] * 10 + resistor_band[1]);

  switch (resistor_band[2]) {
    case 0: break;
    case 1: value *= 10; break;
    case 2: value *= 100; break;
    case 3: value *= 1000; break;
    case 4: value *= 10000; break;
    case 5: value *= 100000; break;
    case 6: value *= 1000000; break;
    case 7: value *= 10000000; break;
    case 8: value *= 100000000; break;
    case 9: value *= 1000000000; break;
  }

  if (value >= 1000) {
    resistor_value.value = value / 1000;
    resistor_value.unit = KILOOHMS;
  } else {
    resistor_value.value = value;
    resistor_value.unit = OHMS;
  }

  return resistor_value;
}