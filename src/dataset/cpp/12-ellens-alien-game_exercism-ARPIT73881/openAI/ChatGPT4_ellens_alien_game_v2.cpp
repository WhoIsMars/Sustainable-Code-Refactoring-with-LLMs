namespace targets {

    class Alien {
    public:
        // Constructor to initialize Alien with coordinates and default health
        Alien(int x, int y) : x_coordinate(x), y_coordinate(y), health(3) {}

        // Getter for health
        int get_health() const noexcept {
            return health;
        }

        // Function to hit the alien (reduce health)
        bool hit() noexcept {
            if (health > 0) {
                --health;
            }
            return health > 0;
        }

        // Function to check if the alien is alive
        bool is_alive() const noexcept {
            return health > 0;
        }

        // Teleport the alien to a new position
        void teleport(int new_x, int new_y) noexcept {
            x_coordinate = new_x;
            y_coordinate = new_y;
        }

        // Check if this alien collides with another alien
        bool collision_detection(const Alien& other) const noexcept {
            return x_coordinate == other.x_coordinate && y_coordinate == other.y_coordinate;
        }

        // Public coordinates
        int x_coordinate;
        int y_coordinate;

    private:
        int health;
    };

} // namespace targets