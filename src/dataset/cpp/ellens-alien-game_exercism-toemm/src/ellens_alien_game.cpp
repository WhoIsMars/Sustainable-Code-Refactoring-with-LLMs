namespace targets {
// TODO: Insert the code for the alien class here
    class Alien {
        public:
            Alien(int x, int y) {
                x_coordinate = x;
                y_coordinate = y;
                health = 3;
            }

        bool hit() {
            health--;
            if (health < 0) health = 0;
            return true;
        }

        bool teleport (int x_new, int y_new) {
            x_coordinate = x_new;
            y_coordinate = y_new;
            return true;
        }

        bool collision_detection (Alien other_alien) {
            
            return x_coordinate == other_alien.x_coordinate &&
                    y_coordinate == other_alien.y_coordinate;
        }

        bool is_alive() {
            return health;
        }
        double get_health() { return health; }

        int x_coordinate {};
        int y_coordinate {};



        private:
            int health;



    };


}  // namespace targets