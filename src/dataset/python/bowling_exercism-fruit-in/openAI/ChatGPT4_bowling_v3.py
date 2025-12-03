class BowlingGame:
    def __init__(self):
        self.frames = []
        self.new_frame = True
        self.remain = 10

    def roll(self, pins):
        if not (0 <= pins <= self.remain):
            raise UnvalidPins(r".+")
        if len(self.frames) == 10 and self.frames[-1][1] == 0:
            raise GameComplete(r".+")

        for frame in self.frames[-2:]:
            if frame[1] > 0:
                frame[0] += pins
                frame[1] -= 1

        if len(self.frames) == 10:
            self.remain -= pins
            return

        if self.new_frame:
            if pins == self.remain:
                self.frames.append([10, 2])
            else:
                self.new_frame = False
                self.remain -= pins
        else:
            if pins == self.remain:
                self.frames.append([10, 1])
            else:
                self.frames.append([10 - self.remain + pins, 0])
            self.new_frame = True
            self.remain = 10

    def score(self):
        return sum(frame[0] for frame in self.frames)


class UnvalidPins(Exception):
    pass


class GameComplete(Exception):
    pass