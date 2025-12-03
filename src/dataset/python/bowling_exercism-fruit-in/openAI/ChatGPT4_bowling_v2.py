class BowlingGame:
    def __init__(self):
        self.frames = []
        self.current_frame = [0, 0]
        self.rolls_remaining = 10

    def roll(self, pins):
        if pins > self.rolls_remaining or pins < 0:
            raise UnvalidPins("Invalid number of pins.")
        if len(self.frames) == 10 and self.frames[-1][1] == 0:
            raise GameComplete("Game is already complete.")

        # Update scores for previous frames
        for frame in self.frames[-2:]:
            if frame[1] > 0:
                frame[0] += pins
                frame[1] -= 1

        # Handle current frame
        if len(self.frames) == 10:
            self.rolls_remaining -= pins % 10
        elif self.current_frame[1] == 0:  # First roll of the frame
            if pins == 10:  # Strike
                self.frames.append([10, 2])
            else:
                self.current_frame = [pins, 0]
                self.rolls_remaining -= pins
        else:  # Second roll of the frame
            self.frames.append([self.current_frame[0] + pins, 0])
            self.current_frame = [0, 0]
            self.rolls_remaining = 10

    def score(self):
        return sum(frame[0] for frame in self.frames)


class UnvalidPins(Exception):
    pass


class GameComplete(Exception):
    pass