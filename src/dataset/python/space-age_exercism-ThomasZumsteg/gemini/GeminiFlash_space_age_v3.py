"""Calculates age on various planets"""

class SpaceAge(object):
    """Calculates age on various planets"""
    _earth_year = 31557600.0  # seconds, float for accurate division
    _ratios = {
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
        """Stores age and pre-calculates planet ages."""
        self.seconds = seconds
        self._planet_years = {}
        for planet, ratio in self._ratios.items():
            self._planet_years[planet] = round(seconds / (self._earth_year * ratio), 2)

    def on_earth(self):
        """Converts seconds to earth years"""
        return self._planet_years['earth']

    def on_mercury(self):
        """Converts seconds to mercury years"""
        return self._planet_years['mercury']

    def on_venus(self):
        """Converts seconds to venus years"""
        return self._planet_years['venus']

    def on_mars(self):
        """Converts seconds to mars years"""
        return self._planet_years['mars']

    def on_jupiter(self):
        """Converts seconds to jupiter years"""
        return self._planet_years['jupiter']

    def on_saturn(self):
        """Converts seconds to saturn years"""
        return self._planet_years['saturn']

    def on_uranus(self):
        """Converts seconds to uranus years"""
        return self._planet_years['uranus']

    def on_neptune(self):
        """Converts seconds to neptune years"""
        return self._planet_years['neptune']