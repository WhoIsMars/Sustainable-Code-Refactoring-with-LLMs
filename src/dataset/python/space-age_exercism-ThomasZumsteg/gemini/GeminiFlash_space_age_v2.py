"""Calculates age on various planets"""

class SpaceAge(object):
    """Calculates age on various planets"""
    _earth_year = 31557600.0  # seconds, float for accurate division
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
        """Stores age and pre-calculates planet years."""
        self.seconds = float(seconds)  # Ensure seconds is a float
        self._planet_years = {}
        for planet, ratio in self._planet_ratios.items():
            self._planet_years[planet] = round(self.seconds / (self._earth_year * ratio), 2)

    def on_earth(self):
        """Returns age on Earth."""
        return self._planet_years['earth']

    def on_mercury(self):
        """Returns age on Mercury."""
        return self._planet_years['mercury']

    def on_venus(self):
        """Returns age on Venus."""
        return self._planet_years['venus']

    def on_mars(self):
        """Returns age on Mars."""
        return self._planet_years['mars']

    def on_jupiter(self):
        """Returns age on Jupiter."""
        return self._planet_years['jupiter']

    def on_saturn(self):
        """Returns age on Saturn."""
        return self._planet_years['saturn']

    def on_uranus(self):
        """Returns age on Uranus."""
        return self._planet_years['uranus']

    def on_neptune(self):
        """Returns age on Neptune."""
        return self._planet_years['neptune']