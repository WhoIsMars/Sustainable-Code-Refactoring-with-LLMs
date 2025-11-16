namespace targets {
  class Alien {
    public:
      int x_coordinate;
      int y_coordinate;

      Alien(int x, int y) : x_coordinate(x), y_coordinate(y) {}

      int get_health() const {
        return health;
      }

      bool is_alive() const {
        return health > 0;
      }

      bool hit() {
        --health;
        return true;
      }

      bool teleport(int x, int y) {
        x_coordinate = x;
        y_coordinate = y;
        return true;
      }

      bool collision_detection(const Alien& a) const {
        return a.x_coordinate == x_coordinate && a.y_coordinate == y_coordinate;
      }

    private:
      int health = 3;
  };

}  // namespace targets