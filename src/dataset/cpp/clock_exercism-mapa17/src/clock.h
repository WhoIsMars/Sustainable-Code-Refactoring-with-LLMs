#if !defined(CLOCK_H)
#define CLOCK_H

#include <string>

namespace date_independent {
    class clock
    {
        public:
            static clock at(const int hour, const int minute);
            clock plus(int minute);
            int getTimeInMinutes() const {return time_in_minutes;}
            
            explicit operator std::string() const;
            bool operator==(const clock &rhs) const {return time_in_minutes == rhs.getTimeInMinutes();};
            bool operator!=(const clock &rhs) const {return !(*this==rhs);};
            
        private:
            clock(const int hour, const int minute);
            int time_in_minutes;
   };
}  // namespace date_independent

#endif // CLOCK_H