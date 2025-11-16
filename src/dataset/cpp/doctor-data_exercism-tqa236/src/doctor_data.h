#include <string>

namespace star_map
{
    enum class System
    {
        Sol,
        BetaHydri,
        EpsilonEridani,
        AlphaCentauri,
        DeltaEridani,
        Omicron2Eridani
    };
}

namespace heaven
{

    class Vessel
    {
    public:
        std::string name;
        int generation;
        star_map::System current_system;
        int busters;

        Vessel(const std::string &name, int generation, star_map::System system = star_map::System::Sol)
            : name(name), generation(generation), current_system(system), busters(0) {}

        Vessel replicate(const std::string &new_name) const
        {
            return Vessel(new_name, this->generation + 1, this->current_system);
        }

        void make_buster()
        {
            ++busters;
        }

        bool shoot_buster()
        {
            if (busters > 0)
            {
                --busters;
                return true;
            }
            return false;
        }
    };

    std::string get_older_bob(const Vessel &vessel1, const Vessel &vessel2);
    bool in_the_same_system(const Vessel &vessel1, const Vessel &vessel2);

}
