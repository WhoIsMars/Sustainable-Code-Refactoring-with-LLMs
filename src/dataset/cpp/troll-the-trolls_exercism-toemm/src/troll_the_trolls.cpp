

namespace hellmath {

// TODO: Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
enum class AccountStatus {
    troll, 
    guest,
    user,
    mod
};


// TODO: Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.
enum class Action {
    read,
    write,
    remove
};

// TODO: Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.
bool display_post (AccountStatus poster, AccountStatus viewer) {
    
    if (poster == AccountStatus::troll and viewer != AccountStatus::troll) {
        return false;
    } else if (poster == AccountStatus::troll and viewer == AccountStatus::troll) {
        return true;
    } else {
        return true;
    }
}

// TODO: Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.
bool permission_check (Action action, AccountStatus accstatus) {

    switch (action)
    {
    case Action::write:
        
        if (accstatus != AccountStatus::guest) return true; // mods, users, trolls can write
        else return false; // guests can't write
    
    case Action::remove:

        if (accstatus == AccountStatus::mod) return true; // only mods can remove posts
        else return false;

    default: // everyone can read posts
        return true;
    }


}

// TODO: Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.

bool valid_player_combination(AccountStatus player1, AccountStatus player2) {


        switch (player1)
        {
        case AccountStatus::mod:
        case AccountStatus::user:
            if (player2 == AccountStatus::mod or player2 == AccountStatus::user) return true;
            else return false;
        case AccountStatus::troll:
            if (player2 == AccountStatus::troll) return true;
            else return false;
        default: // guests cannot play
            return false;
        }


}

// TODO: Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.

bool has_priority (AccountStatus player1, AccountStatus player2) {

    return player1 > player2;


}

}  // namespace hellmath