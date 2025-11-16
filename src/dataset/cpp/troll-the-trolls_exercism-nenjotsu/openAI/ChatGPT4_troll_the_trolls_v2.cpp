namespace hellmath {

  enum class AccountStatus {
    troll,
    guest,
    user,
    mod
  };

  enum class Action {
    read,
    write,
    remove
  };

  inline bool display_post(AccountStatus poster, AccountStatus viewer) {
    return poster != AccountStatus::troll || viewer == AccountStatus::troll;
  }

  inline bool permission_check(Action action, AccountStatus account) {
    if (account == AccountStatus::guest) {
      return action == Action::read;
    }
    if (account == AccountStatus::mod) {
      return true;
    }
    return action != Action::remove;
  }

  inline bool valid_player_combination(AccountStatus player1, AccountStatus player2) {
    return !(player1 == AccountStatus::guest || player2 == AccountStatus::guest ||
             (player1 == AccountStatus::troll) != (player2 == AccountStatus::troll));
  }

  inline bool has_priority(AccountStatus account1, AccountStatus account2) {
    return static_cast<int>(account1) > static_cast<int>(account2);
  }

}  // namespace hellmath