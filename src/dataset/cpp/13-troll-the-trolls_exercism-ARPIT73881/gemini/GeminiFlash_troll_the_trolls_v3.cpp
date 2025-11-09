namespace hellmath
{

    // Task 1: Define an `AccountStatus` enumeration to represent the four account types
    enum class AccountStatus : uint8_t
    {
        troll,
        guest,
        user,
        mod
    };

    // Task 1: Define an `Action` enumeration to represent the three permission types
    enum class Action : uint8_t
    {
        read,
        write,
        remove
    };

    // Task 2: Implement the `display_post` function
    inline bool display_post(AccountStatus poster, AccountStatus viewer) noexcept
    {
        return poster != AccountStatus::troll || viewer == AccountStatus::troll;
    }

    // Task 3: Implement the `permission_check` function
    inline bool permission_check(Action action, AccountStatus status) noexcept
    {
        static constexpr bool permission_table[4][3] = {
            {true, false, false},   // guest: read
            {true, true, false},    // troll: read, write
            {true, true, false},    // user: read, write
            {true, true, true}     // mod: read, write, remove
        };

        return permission_table[static_cast<uint8_t>(status)][static_cast<uint8_t>(action)];
    }

    // Task 4: Implement the `valid_player_combination` function
    inline bool valid_player_combination(AccountStatus player1, AccountStatus player2) noexcept
    {
        if (player1 == AccountStatus::guest || player2 == AccountStatus::guest)
        {
            return false;
        }

        if (player1 == AccountStatus::troll)
        {
            return player2 == AccountStatus::troll;
        }
        if (player2 == AccountStatus::troll)
        {
            return player1 == AccountStatus::troll;
        }

        return true;
    }

    // Task 5: Implement the `has_priority` function
    inline bool has_priority(AccountStatus player1, AccountStatus player2) noexcept
    {
        return static_cast<uint8_t>(player1) > static_cast<uint8_t>(player2);
    }

} // namespace hellmath