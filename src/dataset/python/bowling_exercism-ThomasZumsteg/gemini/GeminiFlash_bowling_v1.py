class BowlingGame(object):
    def __init__(self):
        self._rolls = []
        self._frame = 0
        self._extra_rolls = 0

    def roll(self, pins):
        if self._frame >= 10 and self._extra_rolls <= 0:
            raise IndexError("Game Over")
        if not (0 <= pins <= 10):
            raise ValueError("Cannot score {}".format(pins))
        if self._rolls and len(self._rolls) % 2 == 1 and self._rolls[-1] + pins > 10:
            raise ValueError("Cannot score {} and {}".format(self._rolls[-1], pins))

        self._rolls.append(pins)
        self._update_state(pins)

    def score(self):
        if self._frame < 10 or self._extra_rolls > 0:
            raise IndexError("Game in progress")

        total = 0
        roll_index = 0
        for frame in range(10):
            if self._is_strike(roll_index):
                total += 10 + self._strike_bonus(roll_index)
                roll_index += 1
            elif self._is_spare(roll_index):
                total += 10 + self._spare_bonus(roll_index)
                roll_index += 2
            else:
                total += self._rolls[roll_index] + self._rolls[roll_index + 1]
                roll_index += 2
        return total

    def _update_state(self, pins):
        if pins == 10:
            self._frame += 1
            if self._frame == 10:
                self._extra_rolls = 2
        elif len(self._rolls) % 2 == 0:
            self._frame += 1
            if self._frame == 10 and self._rolls[-2] + pins == 10:
                self._extra_rolls = 1
        
        if self._frame >= 10 and self._extra_rolls > 0:
            self._extra_rolls -= 1

    def _is_strike(self, roll_index):
        return self._rolls[roll_index] == 10

    def _is_spare(self, roll_index):
        return self._rolls[roll_index] + self._rolls[roll_index + 1] == 10

    def _strike_bonus(self, roll_index):
        return self._rolls[roll_index + 1] + (self._rolls[roll_index + 2] if roll_index + 2 < len(self._rolls) else 0)

    def _spare_bonus(self, roll_index):
        return self._rolls[roll_index + 2]