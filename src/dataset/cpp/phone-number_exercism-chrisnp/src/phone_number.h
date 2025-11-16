#pragma once

#include <string>

namespace phone_number {

struct phone_number final {
    explicit phone_number(const std::string&);
    [[nodiscard]] std::string number() const;
    [[nodiscard]] std::string area_code() const;
    [[nodiscard]] std::string exchange() const;
    [[nodiscard]] std::string subscriber() const;
    explicit operator std::string() const;
    private:
        std::string _number;
        std::string _area;
        std::string _exchange;
        std::string _subscriber;
        std::string _formatted;

};

}  // namespace phone_number


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
