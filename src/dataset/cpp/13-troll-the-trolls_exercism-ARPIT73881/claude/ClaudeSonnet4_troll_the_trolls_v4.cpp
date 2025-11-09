namespace hellmath
{
    enum class AccountStatus : uint8_t
    {
        troll,
        guest,
        user,
        mod
    };

    enum class Action : uint8_t
    {
        read,
        write,
        remove
    };

    constexpr bool display_post(AccountStatus poster, AccountStatus viewer) noexcept
    {
        return poster != AccountStatus::troll || viewer == AccountStatus::troll;
    }

    constexpr bool permission_check(Action action, AccountStatus status) noexcept
    {
        constexpr bool permissions[4][3] = {
            {true, true, false},   // troll: read, write, no remove
            {true, false, false},  // guest: read only
            {true, true, false},   // user: read, write, no remove
            {true, true, true}     // mod: all actions
        };
        
        return permissions[static_cast<uint8_t>(status)][static_cast<uint8_t>(action)];
    }

    constexpr bool valid_player_combination(AccountStatus player1, AccountStatus player2) noexcept
    {
        const uint8_t p1 = static_cast<uint8_t>(player1);
        const uint8_t p2 = static_cast<uint8_t>(player2);
        
        constexpr bool compatibility[4][4] = {
            {true, false, false, false},   // troll with: troll, guest, user, mod
            {false, false, false, false},  // guest with: troll, guest, user, mod
            {false, false, true, true},    // user with: troll, guest, user, mod
            {false, false, true, true}     // mod with: troll, guest, user, mod
        };
        
        return compatibility[p1][p2];
    }

    constexpr bool has_priority(AccountStatus player1, AccountStatus player2) noexcept
    {
        return static_cast<uint8_t>(player1) > static_cast<uint8_t>(player2);
    }
}