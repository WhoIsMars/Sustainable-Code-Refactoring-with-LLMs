#if !defined(ROBOT_SIMULATOR_H)
#define ROBOT_SIMULATOR_H

#include <utility>
#include <string>

namespace robot_simulator {
    enum Bearing {NORTH=0, EAST=1, SOUTH=2, WEST=3};
    class Robot{
        public:
            Robot() {x=0;y=0;b=NORTH;};
            Robot(std::pair<int, int> start_pos, Bearing start_bearing)
                {x=start_pos.first; y=start_pos.second; b=start_bearing;};
            const std::pair<int, int> get_position() const;
            Bearing get_bearing() const;

            void turn_right();
            void turn_left();
            void advance();
            void execute_sequence(std::string op_sequence);
        private:
            int x;
            int y;
            Bearing b;
    };
}  // namespace robot_simulator

#endif // ROBOT_SIMULATOR_H