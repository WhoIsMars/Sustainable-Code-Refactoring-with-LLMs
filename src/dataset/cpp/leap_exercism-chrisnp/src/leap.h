#pragma once

namespace leap {
    constexpr auto divBy400(int &year) noexcept -> bool {
        return year % 400 == 0;
    }
    constexpr auto divBy100(int &year) noexcept -> bool {
        return year % 100 == 0;
    }
    constexpr auto divBy004(int &year) noexcept -> bool {
        return year % 4 == 0;
    }
    
    auto is_leap_year(int) noexcept -> bool;

}  // namespace leap
