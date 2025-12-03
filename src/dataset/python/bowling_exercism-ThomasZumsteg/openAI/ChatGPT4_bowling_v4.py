class BowlingGame:
    def __init__(self):
        self._rolls = []
        self._frame = 0
        self._extra_rolls = 0

    def roll(self, pins):
        if self._game_over():
            raise IndexError("Game Over")
        if not (0 <= pins <= 10):
            raise ValueError(f"Cannot score {pins}")
        if self._frame % 2 == 1 and self._rolls[-1] + pins > 10 and self._frame < 18:
            raise ValueError(f"Cannot score {self._rolls[-1]} and {pins}")

        self._rolls.append(pins)
        self._update_state(pins)

    def score(self):
        if not self._game_over():
            raise IndexError("Game in progress")

        total, index = 0, 0
        for frame in range(10):
            if self._rolls[index] == 10:  # Strike
                total += 10 + self._rolls[index + 1] + self._rolls[index + 2]
                index += 1
            elif sum(self._rolls[index:index + 2]) == 10:  # Spare
                total += 10 + self._rolls[index + 2]
                index += 2
            else:  # Open frame
                total += sum(self._rolls[index:index + 2])
                index += 2
        return total

    def _update_state(self, pins):
        if self._frame < 18:  # Regular frames
            self._frame += 2 if pins == 10 and self._frame % 2 == 0 else 1
        elif self._frame == 18:  # 10th frame
            self._extra_rolls = 2 if pins == 10 else 1 if sum(self._rolls[-2:]) == 10 else 0
            self._frame += 1
        elif self._extra_rolls > 0:  # Extra rolls
            self._extra_rolls -= 1

    def _game_over(self):
        return self._frame >= 20 and self._extra_rolls == 0