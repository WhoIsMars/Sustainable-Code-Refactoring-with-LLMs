namespace targets
{
    // TODO: Insert the code for the alien class here
    class Alien
    {
    public:
        Alien(int x, int y)
        {
            x_coordinate = x;
            y_coordinate = y;
            health = 3;
        }
        int x_coordinate;
        int y_coordinate;
        int get_health()
        {
            return health;
        }
        bool hit()
        {
            if (health > 0)
                health -= 1;
            return true;
        }
        bool is_alive()
        {
            return health > 0;
        }
        bool teleport(int x_new, int y_new)
        {
            x_coordinate = x_new;
            y_coordinate = y_new;
            return true;
        }
        bool collision_detection(Alien other)
        {
            return (this->x_coordinate == other.x_coordinate) && (this->y_coordinate == other.y_coordinate);
        }

    private:
        int health;
    };
} // namespace targets