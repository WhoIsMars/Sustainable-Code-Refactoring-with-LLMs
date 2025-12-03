"""Calculates age on various planets"""

class SpaceAge(object):
    """Calculates age on various planets"""
    _earth_year = 31557600  # seconds
    _planet_ratios = {
        'earth': 1.0,
        'mercury': 0.2408467,
        'venus': 0.61519726,
        'mars': 1.8808158,
        'jupiter': 11.862615,
        'saturn': 29.447498,
        'uranus': 84.016846,
        'neptune': 164.79132
    }

    def __init__(self, seconds):
        """Stores age builds functions"""
        self.seconds = seconds

    def on_planet_gen(self, ratio_to_earth):
        """Returns a function that converts seconds into planet years"""
        def on_planet():
            """Converts seconds to planet years"""
            return round(self.seconds / (self._earth_year * ratio_to_earth), 2)
        return on_planet

    def on_earth(self):
        return round(self.seconds / self._earth_year, 2)

    def on_mercury(self):
        return round(self.seconds / (self._earth_year * 0.2408467), 2)

    def on_venus(self):
        return round(self.seconds / (self._earth_year * 0.61519726), 2)

    def on_mars(self):
        return round(self.seconds / (self._earth_year * 1.8808158), 2)

    def on_jupiter(self):
        return round(self.seconds / (self._earth_year * 11.862615), 2)

    def on_saturn(self):
        return round(self.seconds / (self._earth_year * 29.447498), 2)

    def on_uranus(self):
        return round(self.seconds / (self._earth_year * 84.016846), 2)

    def on_neptune(self):
        return round(self.seconds / (self._earth_year * 164.79132), 2)