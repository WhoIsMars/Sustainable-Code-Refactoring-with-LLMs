namespace hellmath {

enum class AccountStatus : unsigned char {
    troll,
    guest,
    user,
    mod,
};

enum class Action : unsigned char {
    read,
    write,
    remove,
};

constexpr bool display_post(AccountStatus s1, AccountStatus s2) noexcept {
    return (s1 == AccountStatus::troll) ? (s2 == AccountStatus::troll) : (s2 != AccountStatus::troll);
}

constexpr bool permission_check(Action action, AccountStatus status) noexcept {
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

constexpr bool valid_player_combination(AccountStatus s1, AccountStatus s2) noexcept {
    return (s1 != AccountStatus::guest && s2 != AccountStatus::guest) &&
           ((s1 == AccountStatus::troll) == (s2 == AccountStatus::troll));
}

constexpr bool has_priority(AccountStatus s1, AccountStatus s2) noexcept {
    return static_cast<unsigned char>(s1) > static_cast<unsigned char>(s2);
}

}  // namespace hellmath