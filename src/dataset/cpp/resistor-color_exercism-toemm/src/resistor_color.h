#pragma once

#include <vector>
#include <string>

namespace resistor_color {


int color_code(const std::string& color) noexcept;

std::vector<std::string> colors() noexcept;



}  // namespace resistor_color
