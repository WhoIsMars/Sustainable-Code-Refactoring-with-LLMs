// eat_ghost returns a boolean value if Pac-Man is able to eat the ghost.
// The function should return true only if Pac-Man has a power pellet active 
// and is touching a ghost.
auto can_eat_ghost(const bool &power_pellet_active, const bool &touching_ghost) -> bool 
{
    if (power_pellet_active) return touching_ghost;
    return 0;
}

// score returns a boolean value if Pac-Man scored. The function should 
// return true if Pac-Man is touching a power pellet or a dot.
auto scored(const bool &touching_power_pellet, const bool &touching_dot) -> bool 
{
    if (touching_power_pellet) return 1;
    return touching_dot;
}

// lost returns a boolean value if Pac-Man loses. The function should 
// return true if Pac-Man is touching a ghost and does not have a power pellet active.
auto lost(const bool &power_pellet_active, const bool &touching_ghost) -> bool 
{
    if (touching_ghost) return !power_pellet_active;
    return 0;
}

// won returns a boolean value if Pac-Man wins. The function should return true
// if Pac-Man has eaten all of the dots and has not lost
auto won(const bool &has_eaten_all_dots, 
         const bool &power_pellet_active, 
         const bool &touching_ghost) -> bool
{
    if (has_eaten_all_dots) return 
        !lost(power_pellet_active, touching_ghost);
    return 0;
}


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif