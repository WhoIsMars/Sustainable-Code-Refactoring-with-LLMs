namespace targets {
  class Alien {
    public:
      int x_coordinate;
      int y_coordinate;

      explicit Alien(int x, int y) : x_coordinate(x), y_coordinate(y), health(3) {}

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

      bool teleport(int x, int y) {
        x_coordinate = x;
        y_coordinate = y;
        return true;
      }

      bool collision_detection(const Alien& a) const {
        return (a.x_coordinate == x_coordinate) && (a.y_coordinate == y_coordinate);
      }

    private:
      int health;
  };

}  // namespace targets