namespace hellmath {

// Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
enum class AccountStatus : unsigned char {
    troll,
    guest,
    user,
    mod,
};

// Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.
enum class Action : unsigned char {
    read,
    write,
    remove,
};

// Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.
inline bool display_post(AccountStatus s1, AccountStatus s2) noexcept {
    return (s1 == AccountStatus::troll) ? (s2 == AccountStatus::troll) : (s2 != AccountStatus::troll);
}

// Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.
inline bool permission_check(Action action, AccountStatus status) noexcept {
    switch (action) {
        case Action::read:
            return true;
        case Action::write:
            return status != AccountStatus::guest;
        case Action::remove:
            return status == AccountStatus::mod;
        default:
            return false;
    }
}

// Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.
inline bool valid_player_combination(AccountStatus s1, AccountStatus s2) noexcept {
    return (s1 != AccountStatus::guest && s2 != AccountStatus::guest) &&
           !((s1 == AccountStatus::troll) ^ (s2 == AccountStatus::troll));
}

// Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.
inline bool has_priority(AccountStatus s1, AccountStatus s2) noexcept {
    return static_cast<unsigned char>(s1) > static_cast<unsigned char>(s2);
}

}  // namespace hellmath