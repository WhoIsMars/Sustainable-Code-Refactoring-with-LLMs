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
        """Stores age"""
        self.seconds = seconds

    def _calculate_age(self, ratio):
        """Converts seconds to planet years"""
        return round(self.seconds / (self._earth_year * ratio), 2)

    def on_earth(self):
        return self._calculate_age(self._planet_ratios['earth'])

    def on_mercury(self):
        return self._calculate_age(self._planet_ratios['mercury'])

    def on_venus(self):
        return self._calculate_age(self._planet_ratios['venus'])

    def on_mars(self):
        return self._calculate_age(self._planet_ratios['mars'])

    def on_jupiter(self):
        return self._calculate_age(self._planet_ratios['jupiter'])

    def on_saturn(self):
        return self._calculate_age(self._planet_ratios['saturn'])

    def on_uranus(self):
        return self._calculate_age(self._planet_ratios['uranus'])

    def on_neptune(self):
        return self._calculate_age(self._planet_ratios['neptune'])