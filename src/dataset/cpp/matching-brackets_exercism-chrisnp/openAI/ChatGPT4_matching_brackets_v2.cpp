#include "matching_brackets.h"

#include <string_view>

bool matching_brackets::check(std::string const &str) {
    std::string_view open = "([{";
    std::string_view close = ")]}";
    char stack[256]; // Fixed-size array to avoid dynamic memory allocation
    int top = -1;

    for (char ch : str) {
        auto open_pos = open.find(ch);
        if (open_pos != std::string_view::npos) {
            if (top == 255) return false; // Prevent stack overflow
            stack[++top] = close[open_pos];
        } else {
            auto close_pos = close.find(ch);
            if (close_pos != std::string_view::npos) {
                if (top == -1 || stack[top--] != ch) return false;
            }
        }
    }
    return top == -1;
}