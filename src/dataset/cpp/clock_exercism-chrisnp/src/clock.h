#pragma once
#include <string>

namespace date_independent {

class clock {

private:
    const int minutes;

public:
    explicit clock(int minutes);
    static clock at(int hours, int minutes = 0);
    explicit operator std::string() const;
    clock plus(int ms) const noexcept;
    clock minus(int ms) const noexcept;
    auto operator==(const clock &other) const noexcept -> bool;
    auto operator!=(const clock &other) const noexcept -> bool;
};

}  // namespace date_independent

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif