namespace hellmath {

// TODO: Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
  enum class AccountStatus : uint8_t {
    troll,
    guest,
    user,
    mod
  };

// TODO: Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.
  enum class Action : uint8_t {
    read,
    write,
    remove
  };

// TODO: Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.
  bool display_post(AccountStatus poster, AccountStatus viewer) {
    return poster != AccountStatus::troll || viewer == AccountStatus::troll;
  }

// TODO: Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.
  bool permission_check(Action action, AccountStatus account) {
    static constexpr bool permissions[4][3] = {
      {true, true, false},   // troll: read, write, no remove
      {true, false, false},  // guest: read only
      {true, true, false},   // user: read, write, no remove
      {true, true, true}     // mod: read, write, remove
    };
    
    return permissions[static_cast<uint8_t>(account)][static_cast<uint8_t>(action)];
  }

// TODO: Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.
  bool valid_player_combination(AccountStatus player1, AccountStatus player2) {
    const bool p1_guest = (player1 == AccountStatus::guest);
    const bool p2_guest = (player2 == AccountStatus::guest);
    const bool p1_troll = (player1 == AccountStatus::troll);
    const bool p2_troll = (player2 == AccountStatus::troll);
    
    return !(p1_guest || p2_guest) && (p1_troll == p2_troll);
  }

// TODO: Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.
  bool has_priority(AccountStatus account1, AccountStatus account2) {
    return account1 > account2;
  }
}  // namespace hellmath