namespace hellmath {

enum class AccountStatus : unsigned char {
  troll,
  guest,
  user,
  mod
};

enum class Action : unsigned char {
  read,
  write,
  remove
};

constexpr bool display_post(AccountStatus poster, AccountStatus viewer) noexcept {
  return poster != AccountStatus::troll || viewer == AccountStatus::troll;
}

constexpr bool permission_check(Action action, AccountStatus account) noexcept {
  constexpr bool permissions[4][3] = {
    {true, true, false},   // troll: read, write, no remove
    {true, false, false},  // guest: read only
    {true, true, false},   // user: read, write, no remove
    {true, true, true}     // mod: read, write, remove
  };
  
  return permissions[static_cast<unsigned char>(account)][static_cast<unsigned char>(action)];
}

constexpr bool valid_player_combination(AccountStatus player1, AccountStatus player2) noexcept {
  const auto p1 = static_cast<unsigned char>(player1);
  const auto p2 = static_cast<unsigned char>(player2);
  
  return (p1 != 1 && p2 != 1) && (p1 == 0) == (p2 == 0);
}

constexpr bool has_priority(AccountStatus account1, AccountStatus account2) noexcept {
  return account1 > account2;
}

}