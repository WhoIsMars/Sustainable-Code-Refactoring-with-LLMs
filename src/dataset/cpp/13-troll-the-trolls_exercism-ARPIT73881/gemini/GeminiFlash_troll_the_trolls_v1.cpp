namespace hellmath
{

    // Task 1: Define an `AccountStatus` enumeration to represent the four account types
    enum class AccountStatus
    {
        troll,
        guest,
        user,
        mod
    };

    // Task 1: Define an `Action` enumeration to represent the three permission types
    enum class Action
    {
        read,
        write,
        remove
    };

    // Task 2: Implement the `display_post` function
    bool display_post(AccountStatus poster, AccountStatus viewer)
    {
        return poster != AccountStatus::troll || viewer == AccountStatus::troll;
    }

    // Task 3: Implement the `permission_check` function
    bool permission_check(Action action, AccountStatus status)
    {
        if (status == AccountStatus::mod)
            return true;

        if (action == Action::read)
            return true;

        return (status == AccountStatus::troll || status == AccountStatus::user) && action == Action::write;
    }

    // Task 4: Implement the `valid_player_combination` function
    bool valid_player_combination(AccountStatus player1, AccountStatus player2)
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
    bool has_priority(AccountStatus player1, AccountStatus player2)
    {
        // Define priority levels: mod > user > guest > troll
        static constexpr int priorities[] = {1, 2, 3, 4};

        int priority1 = priorities[static_cast<int>(player1)];
        int priority2 = priorities[static_cast<int>(player2)];

        // Return true if player1 has strictly higher priority than player2
        return priority1 > priority2;
    }

} // namespace hellmath