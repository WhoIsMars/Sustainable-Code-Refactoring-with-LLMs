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

// Task 2 - Optimized `display_post` function
bool display_post(AccountStatus s1, AccountStatus s2) {
    return (s1 != AccountStatus::troll || s2 == AccountStatus::troll) && 
           (s1 == AccountStatus::troll || s2 != AccountStatus::troll);
}

// Task 3 - Optimized `permission_check` function
bool permission_check(Action action, AccountStatus status) {
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

// Task 4 - Optimized `valid_player_combination` function
bool valid_player_combination(AccountStatus s1, AccountStatus s2) {
    return !(s1 == AccountStatus::guest || s2 == AccountStatus::guest || 
             (s1 == AccountStatus::troll) != (s2 == AccountStatus::troll));
}

// Task 5 - Optimized `has_priority` function
bool has_priority(AccountStatus s1, AccountStatus s2) {
    return s1 > s2;
}

}  // namespace hellmath