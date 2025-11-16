namespace hellmath {

// TODO: Task 1 - Define an `AccountStatus` enumeration to represent the four
// account types: `troll`, `guest`, `user`, and `mod`.
  enum class AccountStatus : unsigned char {
    troll,
    guest,
    user,
    mod
  };

// TODO: Task 1 - Define an `Action` enumeration to represent the three
// permission types: `read`, `write`, and `remove`.
  enum class Action : unsigned char {
    read,
    write,
    remove
  };

// TODO: Task 2 - Implement the `display_post` function, that gets two arguments
// of `AccountStatus` and returns a `bool`. The first argument is the status of
// the poster, the second one is the status of the viewer.
  inline bool display_post(AccountStatus poster, AccountStatus viewer) noexcept {
    return poster != AccountStatus::troll || viewer == AccountStatus::troll;
  }

// TODO: Task 3 - Implement the `permission_check` function, that takes an
// `Action` as a first argument and an `AccountStatus` to check against. It
// should return a `bool`.
  inline bool permission_check(Action action, AccountStatus account) noexcept {
    static constexpr bool permissions[4][3] = {
      {true, true, false},   // troll: read, write, no remove
      {true, false, false},  // guest: read only
      {true, true, false},   // user: read, write, no remove
      {true, true, true}     // mod: read, write, remove
    };
    return permissions[static_cast<unsigned char>(account)][static_cast<unsigned char>(action)];
  }

// TODO: Task 4 - Implement the `valid_player_combination` function that
// checks if two players can join the same game. The function has two parameters
// of type `AccountStatus` and returns a `bool`.
  inline bool valid_player_combination(AccountStatus player1, AccountStatus player2) noexcept {
    return player1 != AccountStatus::guest && 
           player2 != AccountStatus::guest && 
           (player1 == AccountStatus::troll) == (player2 == AccountStatus::troll);
  }

// TODO: Task 5 - Implement the `has_priority` function that takes two
// `AccountStatus` arguments and returns `true`, if and only if the first
// account has a strictly higher priority than the second.
  inline bool has_priority(AccountStatus account1, AccountStatus account2) noexcept {
    return account1 > account2;
  }
}  // namespace hellmath