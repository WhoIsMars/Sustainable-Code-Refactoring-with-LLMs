#pragma once

#include <string>

namespace star_map {

enum class System {
    BetaHydri,
    Sol,
    EpsilonEridani,
    AlphaCentauri,
    DeltaEridani,
    Omicron2Eridani
};

} // namespace star_map

namespace heaven {

using std::string;

struct Vessel {
    Vessel(string name, int generation, 
           star_map::System current_system = star_map::System::Sol);
    auto replicate(string new_name) const -> Vessel;
    auto make_buster() -> void;
    auto shoot_buster() -> bool;
    string name {};
    int generation {};
    star_map::System current_system {};
    int busters { 0 };
};

auto get_older_bob(Vessel const&, Vessel const&) noexcept -> string;
auto in_the_same_system(Vessel const&, Vessel const&) noexcept -> bool;

} // namespace heaven


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif