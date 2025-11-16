namespace hellmath {

  enum class AccountStatus : uint8_t {
    troll,
    guest,
    user,
    mod
  };

  enum class Action : uint8_t {
    read,
    write,
    remove
  };

  inline bool display_post(AccountStatus poster, AccountStatus viewer) {
    return poster != AccountStatus::troll || viewer == AccountStatus::troll;
  }

  inline bool permission_check(Action action, AccountStatus account) {
    static constexpr bool permissions[4][3] = {
      {true,  false, false}, // troll
      {true,  false, false}, // guest
      {true,  true,  false}, // user
      {true,  true,  true}   // mod
    };
    return permissions[static_cast<uint8_t>(account)][static_cast<uint8_t>(action)];
  }

  inline bool valid_player_combination(AccountStatus player1, AccountStatus player2) {
    return !(player1 == AccountStatus::guest || player2 == AccountStatus::guest ||
             (player1 == AccountStatus::troll) != (player2 == AccountStatus::troll));
  }

  inline bool has_priority(AccountStatus account1, AccountStatus account2) {
    return static_cast<uint8_t>(account1) > static_cast<uint8_t>(account2);
  }

}  // namespace hellmath