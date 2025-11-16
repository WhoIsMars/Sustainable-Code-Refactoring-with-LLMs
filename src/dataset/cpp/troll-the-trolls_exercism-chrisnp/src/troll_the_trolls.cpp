namespace hellmath {
// Task 1
enum class AccountStatus : int { troll = 0, guest = 1, user = 2, mod = 3 };
enum class Action : int { read = 1, write = 2, remove = 3 };

using S = AccountStatus;
using A = Action;

// Task 2
[[nodiscard]]
auto display_post(const S &poster, const S &viewer) noexcept -> bool {
    int p = static_cast<int>(poster), 
        v = static_cast<int>(viewer);
    return p != 0 || (p == 0 && p == p + v);
}
// Task 3
[[nodiscard]]
auto permission_check(const A &action, const S &status) noexcept -> bool {
    switch (action) {
        case A::read   : return true;
        case A::write  : return status != S::guest;
        case A::remove : return status == S::mod;
        default        : return false;
    }
}
// Task 4
[[nodiscard]]
auto valid_player_combination(const S &player1, const S &player2) noexcept -> bool {
    int s1 = static_cast<int>(player1), 
        s2 = static_cast<int>(player2);
    return s1 * s2 > 3 || s1 + s2 == 0 ; 
}
// Task 5
[[nodiscard]]
auto has_priority(const S &account1, const S &account2) noexcept -> bool {
    return static_cast<int>(account1) > static_cast<int>(account2);
}
}  // namespace hellmath


#ifndef EXERCISM_RUN_ALL_TESTS
#define EXERCISM_RUN_ALL_TESTS
#endif
