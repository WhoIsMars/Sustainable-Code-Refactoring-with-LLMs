namespace targets {

class Alien {
public:
    Alien(int x, int y) : x_coordinate(x), y_coordinate(y) {}

    int get_health() const {
        return health;
    }

    bool is_alive() const {
        return health > 0;
    }

    bool hit() {
        if (health > 0) {
            --health;
            return true;
        }
        return false;
    }

    void teleport(int x, int y) {
        x_coordinate = x;
        y_coordinate = y;
    }

    bool collision_detection(const Alien& a) const {
        return a.x_coordinate == x_coordinate && a.y_coordinate == y_coordinate;
    }

private:
    int x_coordinate{0};
    int y_coordinate{0};
    int health{3};
};

}  // namespace targets