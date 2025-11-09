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

    bool display_post(AccountStatus poster, AccountStatus viewer) noexcept
    {
        return (poster == AccountStatus::troll) ? (viewer == AccountStatus::troll) 
                                                : (viewer != AccountStatus::troll);
    }

    bool permission_check(Action action, AccountStatus status) noexcept
    {
        switch (status)
        {
            case AccountStatus::troll:
            case AccountStatus::user:
                return action != Action::remove;
            case AccountStatus::guest:
                return action == Action::read;
            case AccountStatus::mod:
                return true;
        }
        return false;
    }

    bool valid_player_combination(AccountStatus player1, AccountStatus player2) noexcept
    {
        if (player1 == AccountStatus::guest || player2 == AccountStatus::guest)
            return false;
        
        const bool p1_troll = (player1 == AccountStatus::troll);
        const bool p2_troll = (player2 == AccountStatus::troll);
        
        return p1_troll == p2_troll;
    }

    bool has_priority(AccountStatus account1, AccountStatus account2) noexcept
    {
        return account1 > account2;
    }
}