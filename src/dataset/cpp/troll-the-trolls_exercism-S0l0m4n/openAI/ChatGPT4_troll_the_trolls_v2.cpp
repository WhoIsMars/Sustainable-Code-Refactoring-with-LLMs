namespace hellmath {

// Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
enum class AccountStatus {
    troll,
    guest,
    user,
    mod,
};

// Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.
enum class Action {
    read,
    write,
    remove,
};

// Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.
inline bool display_post(AccountStatus s1, AccountStatus s2) {
    return (s1 == AccountStatus::troll) ? (s2 == AccountStatus::troll) : (s2 != AccountStatus::troll);
}

// Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.
inline bool permission_check(Action action, AccountStatus status) {
    switch (action) {
        case Action::read:
            return true; // Everyone can read
        case Action::write:
            return status != AccountStatus::guest; // Only guests cannot write
        case Action::remove:
            return status == AccountStatus::mod; // Only moderators can remove
        default:
            return false;
    }
}

// Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.
inline bool valid_player_combination(AccountStatus s1, AccountStatus s2) {
    return !(s1 == AccountStatus::guest || s2 == AccountStatus::guest || 
             (s1 == AccountStatus::troll) != (s2 == AccountStatus::troll));
}

// Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.
inline bool has_priority(AccountStatus s1, AccountStatus s2) {
    return s1 > s2;
}

}  // namespace hellmath