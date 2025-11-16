#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {

    class clock {

        public:
        clock plus(int min) const;
        
        static clock at(int hour, int min);

        // Method that converts an object of clock into a std::string
        operator std::string() const;
        bool operator==(const clock& rhs) const;
        bool operator!=(const clock& rhs) const;

        private:
        clock(int hour, int min);

        int _hour;
        int _min;
        static constexpr int MIN_PER_DAY = 1440;
        
        


    };
}  // namespace date_independent

#endif  // CLOCK_H