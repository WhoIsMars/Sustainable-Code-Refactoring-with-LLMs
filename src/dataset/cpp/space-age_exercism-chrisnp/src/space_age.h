#pragma once
#include <cstdint>

namespace space_age {

class space_age {
    
public:
    explicit space_age(const uint_fast64_t);
    uint_fast64_t seconds() const noexcept;
    auto on_mercury() const noexcept -> float;
    auto on_venus() const noexcept -> float;
    auto on_earth() const noexcept -> float;
    auto on_mars() const noexcept -> float;
    auto on_jupiter() const noexcept -> float;
    auto on_saturn() const noexcept -> float;
    auto on_uranus() const noexcept -> float;
    auto on_neptune() const noexcept -> float;

private:
    uint_fast64_t const age;

};
} // namespace space_age

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif