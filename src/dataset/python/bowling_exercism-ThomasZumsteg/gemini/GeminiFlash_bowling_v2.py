class BowlingGame(object):
    def __init__(self):
        self._rolls = []
        self._frame = 0
        self._first = True
        self._extra_rolls = 0

    def roll(self, pins):
        if self._game_over():
            raise IndexError("Game Over")
        if not (0 <= pins <= 10):
            raise ValueError("Cannot score {}".format(pins))
        if not self._first and pins + self._rolls[-1] > 10:
            raise ValueError("Cannot score {} and {}".format(self._rolls[-1], pins))

        self._rolls.append(pins)
        self._update_state(pins)

    def score(self):
        if not self._game_over():
            raise IndexError("Game in progress")

        total = 0
        frame_index = 0
        for frame in range(10):
            if self._is_strike(frame_index):
                total += 10 + self._strike_bonus(frame_index)
                frame_index += 1
            elif self._is_spare(frame_index):
                total += 10 + self._spare_bonus(frame_index)
                frame_index += 2
            else:
                total += self._sum_of_balls_in_frame(frame_index)
                frame_index += 2
        return total

    def _is_strike(self, frame_index):
        return self._rolls[frame_index] == 10

    def _is_spare(self, frame_index):
        return self._rolls[frame_index] + self._rolls[frame_index+1] == 10

    def _strike_bonus(self, frame_index):
        return self._rolls[frame_index+1] + self._rolls[frame_index+2]

    def _spare_bonus(self, frame_index):
        return self._rolls[frame_index+2]

    def _sum_of_balls_in_frame(self, frame_index):
        return self._rolls[frame_index] + self._rolls[frame_index+1]

    def _update_state(self, pins):
        strike = pins == 10
        if self._frame < 20:
            self._frame += 2 if strike else 1
        self._first = not strike if not self._first else True

        if self._frame == 20:
            if strike:
                self._extra_rolls = 2
            elif len(self._rolls) > 1 and self._rolls[-2] + self._rolls[-1] == 10:
                self._extra_rolls = 1

    def _game_over(self):
        return self._frame >= 20 and self._extra_rolls == 0