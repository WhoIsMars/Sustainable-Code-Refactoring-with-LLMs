class Clock:
    __slots__ = 'hour', 'minute'

    def __init__(self, hour, minute):
        total_minutes = (hour * 60 + minute) % 1440
        self.hour = total_minutes // 60
        self.minute = total_minutes % 60

    def __repr__(self):
        return f'{self.hour:02}:{self.minute:02}'

    def __eq__(self, other):
        return (self.hour, self.minute) == (other.hour, other.minute)

    def __add__(self, minutes):
        return Clock(self.hour, self.minute + minutes)

    def __sub__(self, minutes):
        return Clock(self.hour, self.minute - minutes)