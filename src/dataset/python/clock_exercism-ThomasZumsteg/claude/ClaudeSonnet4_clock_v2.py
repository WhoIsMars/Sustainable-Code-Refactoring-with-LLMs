class Clock:
    __slots__ = ('hour', 'minute')
    
    def __init__(self, hour, minute):
        total_minutes = hour * 60 + minute
        total_minutes %= 1440  # 24 * 60
        self.hour = total_minutes // 60
        self.minute = total_minutes % 60

    def __repr__(self):
        return f'{self.hour:02}:{self.minute:02}'

    def __eq__(self, other):
        return self.hour == other.hour and self.minute == other.minute

    def __add__(self, minutes):
        total_minutes = self.hour * 60 + self.minute + minutes
        total_minutes %= 1440
        return Clock(0, total_minutes)

    def __sub__(self, minutes):
        total_minutes = self.hour * 60 + self.minute - minutes
        total_minutes %= 1440
        return Clock(0, total_minutes)