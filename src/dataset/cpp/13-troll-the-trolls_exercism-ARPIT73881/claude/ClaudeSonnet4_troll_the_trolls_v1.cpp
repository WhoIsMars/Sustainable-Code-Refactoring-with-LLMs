namespace hellmath
{

    // Task 1: Define an `AccountStatus` enumeration to represent the four account types
    enum class AccountStatus : uint8_t
    {
        troll = 0,
        guest = 1,
        user = 2,
        mod = 3
    };

    // Task 1: Define an `Action` enumeration to represent the three permission types
    enum class Action : uint8_t
    {
        read = 0,
        write = 1,
        remove = 2
    };

    // Task 2: Implement the `display_post` function
    bool display_post(AccountStatus poster, AccountStatus viewer)
    {
        return poster != AccountStatus::troll || viewer == AccountStatus::troll;
    }

    // Task 3: Implement the `permission_check` function
    bool permission_check(Action action, AccountStatus status)
    {
        // Use bit manipulation for faster permission checking
        // Permissions encoded as bits: read=1, write=2, remove=4
        static constexpr uint8_t permissions[] = {
            1,  // guest: read only
            3,  // troll: read + write
            3,  // user: read + write
            7   // mod: read + write + remove
        };
        
        const uint8_t action_bit = 1u << static_cast<uint8_t>(action);
        return (permissions[static_cast<uint8_t>(status)] & action_bit) != 0;
    }

    // Task 4: Implement the `valid_player_combination` function
    bool valid_player_combination(AccountStatus player1, AccountStatus player2)
    {
        const uint8_t p1 = static_cast<uint8_t>(player1);
        const uint8_t p2 = static_cast<uint8_t>(player2);
        
        // Guests cannot play with anyone
        if (p1 == 1 || p2 == 1) return false;
        
        // Trolls can only play with other trolls
        if (p1 == 0 || p2 == 0) return p1 == 0 && p2 == 0;
        
        // Users and mods can play together
        return true;
    }

    // Task 5: Implement the `has_priority` function
    bool has_priority(AccountStatus player1, AccountStatus player2)
    {
        // Priority is directly encoded in enum values: mod(3) > user(2) > guest(1) > troll(0)
        return static_cast<uint8_t>(player1) > static_cast<uint8_t>(player2);
    }

} // namespace hellmath