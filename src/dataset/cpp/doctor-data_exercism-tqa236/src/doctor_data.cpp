#include "doctor_data.h"

namespace heaven
{

    std::string get_older_bob(const Vessel &vessel1, const Vessel &vessel2)
    {
        return vessel1.generation < vessel2.generation ? vessel1.name : vessel2.name;
    }

    bool in_the_same_system(const Vessel &vessel1, const Vessel &vessel2)
    {
        return vessel1.current_system == vessel2.current_system;
    }

}