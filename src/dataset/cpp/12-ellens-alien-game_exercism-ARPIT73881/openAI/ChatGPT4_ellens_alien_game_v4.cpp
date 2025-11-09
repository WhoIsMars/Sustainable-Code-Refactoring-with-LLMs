namespace targets {

    class Alien {
    public:
        Alien(int x, int y) noexcept : x_coordinate(x), y_coordinate(y), health(3) {}

        int get_health() const noexcept {
            return health;
        }

        bool hit() noexcept {
            if (health > 0) {
                --health;
            }
            return health > 0;
        }

        bool is_alive() const noexcept {
            return health > 0;
        }

        bool teleport(int new_x, int new_y) noexcept {
            x_coordinate = new_x;
            y_coordinate = new_y;
            return true;
        }

        bool collision_detection(const Alien& other) const noexcept {
            return x_coordinate == other.x_coordinate && y_coordinate == other.y_coordinate;
        }

        int x_coordinate;
        int y_coordinate;

    private:
        unsigned char health;
    };

} // namespace targets