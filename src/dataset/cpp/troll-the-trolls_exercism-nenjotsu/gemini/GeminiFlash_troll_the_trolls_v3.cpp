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
    switch (account) {
      case AccountStatus::guest:
        return action == Action::read;
      case AccountStatus::user:
      case AccountStatus::troll:
        return action <= Action::write;
      case AccountStatus::mod:
        return true;
      default:
        return false;
    }
  }

  bool valid_player_combination(AccountStatus player1, AccountStatus player2) {
    if (player1 == AccountStatus::guest || player2 == AccountStatus::guest) {
      return false;
    }
    return player1 == player2 || (player1 != AccountStatus::troll && player2 != AccountStatus::troll);
  }

  bool has_priority(AccountStatus account1, AccountStatus account2) {
    return static_cast<int>(account1) > static_cast<int>(account2);
  }
}  // namespace hellmath