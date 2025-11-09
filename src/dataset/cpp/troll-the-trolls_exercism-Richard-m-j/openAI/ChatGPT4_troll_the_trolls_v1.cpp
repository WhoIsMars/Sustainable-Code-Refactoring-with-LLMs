namespace hellmath
{
    enum class AccountStatus
    {
        troll,
        guest,
        user,
        mod
    };

    enum class Action
    {
        read,
        write,
        remove
    };

    bool display_post(AccountStatus poster, AccountStatus viewer)
    {
        return !(poster == AccountStatus::troll && viewer != AccountStatus::troll) && viewer != AccountStatus::troll;
    }

    bool permission_check(Action action, AccountStatus status)
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
        default:
            return false;
        }
    }

    bool valid_player_combination(AccountStatus player1, AccountStatus player2)
    {
        return !(player1 == AccountStatus::guest || player2 == AccountStatus::guest || 
                 (player1 == AccountStatus::troll && player2 != AccountStatus::troll) || 
                 (player2 == AccountStatus::troll && player1 != AccountStatus::troll));
    }

    bool has_priority(AccountStatus account1, AccountStatus account2)
    {
        return account1 > account2;
    }
} // namespace hellmath