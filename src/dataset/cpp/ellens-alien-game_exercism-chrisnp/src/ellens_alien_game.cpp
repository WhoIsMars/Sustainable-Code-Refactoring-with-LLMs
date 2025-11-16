namespace {
template<typename T> constexpr auto max(T x, T y) noexcept -> T { 
    return x > y ? x : y; 
}
template<typename T> void swap(T &x, T &y) {
    T tmp {x};
    x = y;
    y = tmp;
}
}  // namespace


namespace targets {

class Alien {
public:
    int x_coordinate;
    int y_coordinate;
    
    [[nodiscard]]
    Alien(int x, int y): x_coordinate { x }, y_coordinate { y } {}

    int get_health() const { return health; }

    bool hit() {
        --health;
        health = max(0, health);
        return true;
    }

    bool is_alive() { return get_health() > 0; }

    bool teleport(int x, int y) {
        swap(x_coordinate, x);
        swap(y_coordinate, y);
        return true;
    }

    bool collision_detection(Alien other) {
        int delta_xs = x_coordinate - other.x_coordinate;
        int delta_ys = y_coordinate - other.y_coordinate;
        return  delta_xs == 0 && delta_ys == 0;
    }

private: 
    int health { 3 };

};

}  // namespace targets



#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif