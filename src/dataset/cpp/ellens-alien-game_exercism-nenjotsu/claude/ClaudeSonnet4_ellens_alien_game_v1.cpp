namespace targets {
  class Alien {
    public:
      int x_coordinate{0};
      int y_coordinate{0};
      
      Alien(int x, int y) noexcept : x_coordinate(x), y_coordinate(y) {}
      
      inline int get_health() const noexcept {
        return health;
      }
      
      inline bool is_alive() const noexcept {
        return health > 0;
      }
      
      inline bool hit() noexcept {
        --health;
        return true;
      }
      
      inline bool teleport(int x, int y) noexcept {
        x_coordinate = x;
        y_coordinate = y;
        return true;
      }
      
      inline bool collision_detection(const Alien& a) const noexcept {
        return a.x_coordinate == x_coordinate && a.y_coordinate == y_coordinate;
      }

    private:
      int health{3};
  };
}  // namespace targets