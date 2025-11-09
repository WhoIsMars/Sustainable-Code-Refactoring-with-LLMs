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
        return poster != AccountStatus::troll || viewer == AccountStatus::troll;
    }

    bool permission_check(Action action, AccountStatus status)
    {
        if (status == AccountStatus::mod)
            return true;
        if (action == Action::read)
            return true;
        return (status == AccountStatus::troll || status == AccountStatus::user) && action == Action::write;
    }

    bool valid_player_combination(AccountStatus player1, AccountStatus player2)
    {
        if (player1 == AccountStatus::guest || player2 == AccountStatus::guest)
            return false;
        if (player1 == AccountStatus::troll || player2 == AccountStatus::troll)
            return player1 == AccountStatus::troll && player2 == AccountStatus::troll;
        return true;
    }

    bool has_priority(AccountStatus player1, AccountStatus player2)
    {
        return static_cast<int>(player1) > static_cast<int>(player2);
    }

} // namespace hellmath