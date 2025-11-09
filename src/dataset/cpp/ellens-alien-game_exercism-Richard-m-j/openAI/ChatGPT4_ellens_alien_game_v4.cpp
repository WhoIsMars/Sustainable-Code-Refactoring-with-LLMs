namespace targets
{
    class Alien
    {
    public:
        Alien(int x, int y) : x_coordinate(x), y_coordinate(y), health(3) {}

        int get_health() const noexcept { return health; }

        bool hit() noexcept
        {
            if (health > 0)
            {
                --health;
                return true;
            }
            return false;
        }

        bool is_alive() const noexcept { return health > 0; }

        void teleport(int x_new, int y_new) noexcept
        {
            x_coordinate = x_new;
            y_coordinate = y_new;
        }

        bool collision_detection(const Alien& other) const noexcept
        {
            return x_coordinate == other.x_coordinate && y_coordinate == other.y_coordinate;
        }

    private:
        int x_coordinate;
        int y_coordinate;
        int health;
    };
} // namespace targets