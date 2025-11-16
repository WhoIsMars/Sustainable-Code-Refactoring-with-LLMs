namespace targets {
  class Alien {
    public:
      int x_coordinate{0};
      int y_coordinate{0};
      
      Alien(int x, int y) noexcept : x_coordinate(x), y_coordinate(y) {}
      
      int get_health() const noexcept {
        return health;
      }
      
      bool is_alive() const noexcept {
        return health > 0;
      }
      
      bool hit() noexcept {
        --health;
        return true;
      }
      
      bool teleport(int x, int y) noexcept {
        x_coordinate = x;
        y_coordinate = y;
        return true;
      }
      
      bool collision_detection(const Alien& a) const noexcept {
        return a.x_coordinate == x_coordinate && a.y_coordinate == y_coordinate;
      }

    private:
      int health{3};
  };
}