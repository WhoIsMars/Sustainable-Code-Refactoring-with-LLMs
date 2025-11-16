namespace targets {
  class Alien {
    public:
      int x_coordinate{0};
      int y_coordinate{0};
      
      Alien(int x, int y) : x_coordinate(x), y_coordinate(y) {}
      
      inline int get_health() const {
        return health;
      }
      
      inline bool is_alive() const {
        return health > 0;
      }
      
      inline void hit() {
        --health;
      }
      
      inline void teleport(int x, int y) {
        x_coordinate = x;
        y_coordinate = y;
      }
      
      inline bool collision_detection(const Alien& a) const {
        return a.x_coordinate == x_coordinate && a.y_coordinate == y_coordinate;
      }

    private:
      int health{3};
  };
}  // namespace targets