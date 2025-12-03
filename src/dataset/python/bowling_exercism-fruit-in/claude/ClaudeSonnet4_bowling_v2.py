class BowlingGame:
    def __init__(self):
        self.frames = []
        self.new_frame = True
        self.remain = 10

    def roll(self, pins):
        if pins > self.remain or pins < 0:
            raise UnvalidPins(r".+")
        
        frames_len = len(self.frames)
        if frames_len == 10 and self.frames[9][1] == 0:
            raise GameComplete(r".+")

        # Update bonus scores for previous frames
        start_idx = max(frames_len - 2, 0)
        for i in range(start_idx, frames_len):
            frame = self.frames[i]
            if frame[1] > 0:
                frame[0] += pins
                frame[1] -= 1

        if frames_len == 10:
            self.remain -= pins % 10
        elif pins == self.remain:
            if self.new_frame:
                self.frames.append([10, 2])
            else:
                self.frames.append([10, 1])
                self.new_frame = True
                self.remain = 10
        elif not self.new_frame:
            self.frames.append([10 - self.remain + pins, 0])
            self.new_frame = True
            self.remain = 10
        else:
            self.new_frame = False
            self.remain -= pins

    def score(self):
        total = 0
        for frame in self.frames:
            total += frame[0]
        return total


class UnvalidPins(Exception):
    pass


class GameComplete(Exception):
    pass