#pragma once
#include <string>
#include <random>
#include <set>

namespace robot_name {

class robot {

public:
    [[nodiscard]] explicit robot();
    auto reset() noexcept -> void;
    [[nodiscard]] 
    auto name() const noexcept -> std::string const&;
private:
    std::string robot_name {};
    std::set<std::string> names_history {};
};

}  // namespace robot_name


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif