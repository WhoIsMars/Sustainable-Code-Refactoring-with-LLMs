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

  bool display_post(AccountStatus poster, AccountStatus viewer) {
    return poster != AccountStatus::troll || viewer == AccountStatus::troll;
  }

  bool permission_check(Action action, AccountStatus account) {
    if (account == AccountStatus::guest) {
      return action == Action::read;
    }
    if (account == AccountStatus::mod) {
      return true;
    }
    return action != Action::remove;
  }

  bool valid_player_combination(AccountStatus player1, AccountStatus player2) {
    if (player1 == AccountStatus::guest || player2 == AccountStatus::guest) {
      return false;
    }
    return player1 == player2 || (player1 != AccountStatus::troll && player2 != AccountStatus::troll);
  }

  bool has_priority(AccountStatus account1, AccountStatus account2) {
    return account1 > account2;
  }
}  // namespace hellmath