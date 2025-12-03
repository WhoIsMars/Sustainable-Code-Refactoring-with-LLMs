class BowlingGame:
    def __init__(self):
        self.frames = []
        self.frame_index = 0
        self.rolls = []

    def roll(self, pins):
        if not 0 <= pins <= 10:
            raise UnvalidPins("Invalid number of pins")

        if self.frame_index == 10 and self.rolls[-1] != 10 and sum(self.rolls[-2:]) < 10:
            raise GameComplete("Game is complete")

        self.rolls.append(pins)

    def score(self):
        score = 0
        roll_index = 0
        for frame_index in range(10):
            if self.rolls[roll_index] == 10:  # Strike
                score += 10 + self.strike_bonus(roll_index)
                roll_index += 1
            elif sum(self.rolls[roll_index:roll_index+2]) == 10:  # Spare
                score += 10 + self.spare_bonus(roll_index)
                roll_index += 2
            else:
                score += sum(self.rolls[roll_index:roll_index+2])
                roll_index += 2
        return score

    def strike_bonus(self, roll_index):
        return sum(self.rolls[roll_index+1:roll_index+3])

    def spare_bonus(self, roll_index):
        return self.rolls[roll_index+2]


class UnvalidPins(Exception):
    pass


class GameComplete(Exception):
    pass