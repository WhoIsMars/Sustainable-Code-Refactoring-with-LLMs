namespace targets
{
    class Alien
    {
    public:
        Alien(int x, int y) : x_coordinate(x), y_coordinate(y) {}
        
        int x_coordinate;
        int y_coordinate;
        
        inline int get_health() const noexcept
        {
            return health;
        }
        
        inline bool hit() noexcept
        {
            return health > 0 ? (--health, true) : false;
        }
        
        inline bool is_alive() const noexcept
        {
            return health > 0;
        }
        
        inline bool teleport(int x_new, int y_new) noexcept
        {
            x_coordinate = x_new;
            y_coordinate = y_new;
            return true;
        }
        
        inline bool collision_detection(const Alien& other) const noexcept
        {
            return x_coordinate == other.x_coordinate && y_coordinate == other.y_coordinate;
        }

    private:
        int health = 3;
    };
}