class BowlingGame(object):
    def __init__(self):
        self._rolls = []
        self._frame = 0
        self._first = True
        self._extra_rolls = None

    def roll(self, pins):
        if self._game_over():
            raise IndexError("Game Over")
        if not (0 <= pins <= 10):
            raise ValueError("Cannot score {}".format(pins))
        if not self._first and pins + self._rolls[-1] > 10:
            raise ValueError("Cannot score {} and {}".format(self._rolls[-1], pins))

        self._rolls.append(pins)
        self._update_state()

    def score(self):
        if not self._game_over():
            raise IndexError("Game in progress")

        index = frame = total = 0
        rolls = self._rolls
        rolls_len = len(rolls)
        
        while index < rolls_len and frame < 10:
            first = rolls[index]
            second = rolls[index + 1] if index + 1 < rolls_len else 0
            
            if first == 10:  # strike
                third = rolls[index + 2] if index + 2 < rolls_len else 0
                total += 10 + second + third
                index += 1
            elif first + second == 10:  # spare
                third = rolls[index + 2] if index + 2 < rolls_len else 0
                total += 10 + third
                index += 2
            else:  # regular frame
                total += first + second
                index += 2
            
            frame += 1
        
        return total

    def _update_state(self):
        strike = self._rolls[-1] == 10

        self._frame = min(20, self._frame + (2 if strike else 1))
        self._first = True if strike else not self._first

        if self._frame == 20 and self._extra_rolls is None: 
            if strike:
                self._extra_rolls = 2
            elif len(self._rolls) >= 2 and self._rolls[-2] + self._rolls[-1] == 10:
                self._extra_rolls = 1
            else:
                self._extra_rolls = 0
        elif self._extra_rolls is not None:
            self._extra_rolls -= 1

    def _game_over(self):
        return self._frame >= 20 and (self._extra_rolls is None or self._extra_rolls <= 0)