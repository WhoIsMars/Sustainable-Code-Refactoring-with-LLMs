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
        constexpr uint8_t permissions[] = {
            0b001, // troll: read
            0b001, // guest: read
            0b011, // user: read, write
            0b111  // mod: read, write, remove
        };
        
        return permissions[static_cast<uint8_t>(status)] & (1 << static_cast<uint8_t>(action));
    }

    constexpr bool valid_player_combination(AccountStatus player1, AccountStatus player2) noexcept
    {
        constexpr uint8_t compatibility_matrix[] = {
            0b0001, // troll: only with troll
            0b0000, // guest: with nobody
            0b1100, // user: with user or mod
            0b1100  // mod: with user or mod
        };
        
        return compatibility_matrix[static_cast<uint8_t>(player1)] & 
               (1 << static_cast<uint8_t>(player2));
    }

    constexpr bool has_priority(AccountStatus player1, AccountStatus player2) noexcept
    {
        return static_cast<uint8_t>(player1) > static_cast<uint8_t>(player2);
    }

} // namespace hellmath