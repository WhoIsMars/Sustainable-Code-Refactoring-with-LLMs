namespace hellmath {

enum class AccountStatus {
    troll,
    guest,
    user,
    mod,
};

enum class Action {
    read,
    write,
    remove,
};

inline bool display_post(AccountStatus s1, AccountStatus s2) {
    return (s1 == AccountStatus::troll) ? (s2 == AccountStatus::troll) : (s2 != AccountStatus::troll);
}

inline bool permission_check(Action action, AccountStatus status) {
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

inline bool valid_player_combination(AccountStatus s1, AccountStatus s2) {
    return !(s1 == AccountStatus::guest || s2 == AccountStatus::guest || 
             (s1 == AccountStatus::troll) != (s2 == AccountStatus::troll));
}

inline bool has_priority(AccountStatus s1, AccountStatus s2) {
    return s1 > s2;
}

}  // namespace hellmath