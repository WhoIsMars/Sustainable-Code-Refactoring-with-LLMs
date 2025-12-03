class Clock(object):
    def __init__(self, hour, minute):
        total_minutes = hour * 60 + minute
        self.hour = (total_minutes // 60) % 24
        self.minute = total_minutes % 60

    def __repr__(self):
        return '{:02}:{:02}'.format(self.hour, self.minute)

    def __eq__(self, other):
        return self.hour == other.hour and self.minute == other.minute

    def __add__(self, minutes):
        new_total_minutes = self.hour * 60 + self.minute + minutes
        return Clock(0, new_total_minutes)

    def __sub__(self, minutes):
        new_total_minutes = self.hour * 60 + self.minute - minutes
        return Clock(0, new_total_minutes)