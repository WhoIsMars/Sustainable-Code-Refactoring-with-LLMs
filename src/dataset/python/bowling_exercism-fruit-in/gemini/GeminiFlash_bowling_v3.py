class BowlingGame:
    def __init__(self):
        self.frames = []
        self.frame_index = 0
        self.rolls = []
        self.game_over = False

    def roll(self, pins):
        if self.game_over:
            raise GameComplete("Game is already complete.")
        if not 0 <= pins <= 10:
            raise UnvalidPins("Invalid number of pins.")

        self.rolls.append(pins)

        if len(self.frames) < 10:
            if len(self.rolls) % 2 == 0 or pins == 10:
                self.frames.append([])

        if len(self.frames) == 10:
            if len(self.rolls) > 21:
                self.game_over = True
                return

    def score(self):
        score = 0
        roll_index = 0
        for frame_index in range(10):
            if self.is_strike(roll_index):
                score += 10 + self.strike_bonus(roll_index)
                roll_index += 1
            elif self.is_spare(roll_index):
                score += 10 + self.spare_bonus(roll_index)
                roll_index += 2
            else:
                score += self.sum_of_balls_in_frame(roll_index)
                roll_index += 2
        return score

    def is_strike(self, roll_index):
        return self.rolls[roll_index] == 10

    def is_spare(self, roll_index):
        return self.rolls[roll_index] + self.rolls[roll_index + 1] == 10

    def strike_bonus(self, roll_index):
        return self.rolls[roll_index + 1] + self.rolls[roll_index + 2]

    def spare_bonus(self, roll_index):
        return self.rolls[roll_index + 2]

    def sum_of_balls_in_frame(self, roll_index):
        return self.rolls[roll_index] + self.rolls[roll_index + 1]


class UnvalidPins(Exception):
    pass


class GameComplete(Exception):
    pass