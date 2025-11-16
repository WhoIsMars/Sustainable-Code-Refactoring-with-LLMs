#pragma once
#include <string>

namespace star_map {
    enum class System {
        BetaHydri,
        EpsilonEridani,
        Sol,
        Omicron2Eridani,
        AlphaCentauri,
        DeltaEridani,
    };
}

namespace heaven {
    class Vessel {
        private:

        public:
            Vessel (std::string name="", int i=1, star_map::System sys=star_map::System::Sol);

            Vessel replicate(std::string newname);
            void make_buster();
            bool shoot_buster();

            int busters;
            std::string name;
            int generation;
            star_map::System current_system;
    };

    std::string get_older_bob(const Vessel& ves1,const Vessel& ves2);
    bool in_the_same_system(Vessel& ves1, Vessel& ves2);
}

