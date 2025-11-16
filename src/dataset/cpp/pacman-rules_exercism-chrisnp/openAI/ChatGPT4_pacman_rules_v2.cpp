auto can_eat_ghost(const bool power_pellet_active, const bool touching_ghost) -> bool 
{
    return power_pellet_active && touching_ghost;
}

auto scored(const bool touching_power_pellet, const bool touching_dot) -> bool 
{
    return touching_power_pellet || touching_dot;
}

auto lost(const bool power_pellet_active, const bool touching_ghost) -> bool 
{
    return touching_ghost && !power_pellet_active;
}

auto won(const bool has_eaten_all_dots, 
         const bool power_pellet_active, 
         const bool touching_ghost) -> bool
{
    return has_eaten_all_dots && !lost(power_pellet_active, touching_ghost);
}

#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif