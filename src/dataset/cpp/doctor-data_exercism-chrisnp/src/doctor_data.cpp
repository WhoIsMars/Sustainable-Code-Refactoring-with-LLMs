#include "doctor_data.h"

heaven::Vessel::Vessel( 
    string name, int generation, star_map::System current_system
) : name(name), generation(generation), 
    current_system(current_system), busters(0) {}

heaven::Vessel heaven::Vessel::replicate(string new_name) const 
{
    Vessel replica { new_name, generation + 1 };
    return replica;
}

void heaven::Vessel::make_buster() 
{
    ++busters;
}

bool heaven::Vessel::shoot_buster() 
{
    return !(--busters < 0);
}

std::string heaven::get_older_bob(heaven::Vessel const &bob_v1, 
                                  heaven::Vessel const &bob_v2) noexcept
{
    return (bob_v2.generation > bob_v1.generation ? bob_v1 : bob_v2).name;
}

bool heaven::in_the_same_system(heaven::Vessel const &v1, 
                                heaven::Vessel const &v2) noexcept
{
    return v1.current_system == v2.current_system;
}