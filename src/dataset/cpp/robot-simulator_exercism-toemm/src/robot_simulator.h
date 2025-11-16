#if !defined(ROBOT_SIMULATOR_H)
#define ROBOT_SIMULATOR_H

#include <utility>
#include <string>

namespace robot_simulator {

typedef std::pair<int, int> Coordinates;

enum class Bearing {
    NORTH, SOUTH, EAST, WEST
};

class Robot {


    public:
    Robot(std::pair<int, int> position = {0, 0}, Bearing bearing = Bearing::NORTH);
    Coordinates get_position() const;
    Bearing get_bearing() const;

    void turn_right();
    void turn_left();
    void advance();
    void execute_sequence(const std::string& seq);

    private:
    Bearing _bearing;
    Coordinates _pos;

};


}  // namespace robot_simulator

#endif  // ROBOT_SIMULATOR_H