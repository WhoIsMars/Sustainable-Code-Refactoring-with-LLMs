class BowlingGame(object):
    def __init__(self):
        self._rolls = []
        self._frame = 0
        self._first = True
        self._extra_rolls = 0

    def roll(self, pins):
        if self._frame >= 20 and self._extra_rolls <= 0:
            raise IndexError("Game Over")

        if not (0 <= pins <= 10):
            raise ValueError("Cannot score {}".format(pins))

        if not self._first and len(self._rolls) > 0 and pins + self._rolls[-1] > 10:
            raise ValueError("Cannot score {} and {}".format(self._rolls[-1], pins))

        self._rolls.append(pins)
        self._update_state(pins)

    def score(self):
        if self._frame < 20 or self._extra_rolls > 0:
            raise IndexError("Game in progress")

        total = 0
        index = 0
        for frame in range(10):
            first = self._rolls[index]
            if first == 10:  # Strike
                second = self._rolls[index + 1] if index + 1 < len(self._rolls) else 0
                third = self._rolls[index + 2] if index + 2 < len(self._rolls) else 0
                total += 10 + second + third
                index += 1
            else:
                second = self._rolls[index + 1]
                if first + second == 10:  # Spare
                    third = self._rolls[index + 2] if index + 2 < len(self._rolls) else 0
                    total += 10 + third
                else:
                    total += first + second
                index += 2
        return total

    def _update_state(self, pins):
        strike = pins == 10

        if strike:
            self._frame += 2
            self._first = True
        else:
            self._frame += 1
            self._first = not self._first

        if self._frame == 20:
            if strike:
                self._extra_rolls = 2
            elif len(self._rolls) >= 2 and sum(self._rolls[-2:]) == 10:
                self._extra_rolls = 1
        elif self._extra_rolls > 0:
            self._extra_rolls -= 1

    def _game_over(self):
        return self._frame >= 20 and self._extra_rolls <= 0