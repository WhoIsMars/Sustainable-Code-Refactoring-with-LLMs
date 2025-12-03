"""Calculates age on various planets"""

class SpaceAge(object):
    """Calculates age on various planets"""
    _earth_year = 31557600.0  # seconds, float for accurate division
    _planet_ratios = {
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
        self._earth_age = self.seconds / self._earth_year

    def on_earth(self):
        """Converts seconds to Earth years"""
        return round(self._earth_age, 2)

    def on_mercury(self):
        """Converts seconds to Mercury years"""
        return round(self._earth_age / self._planet_ratios['mercury'], 2)

    def on_venus(self):
        """Converts seconds to Venus years"""
        return round(self._earth_age / self._planet_ratios['venus'], 2)

    def on_mars(self):
        """Converts seconds to Mars years"""
        return round(self._earth_age / self._planet_ratios['mars'], 2)

    def on_jupiter(self):
        """Converts seconds to Jupiter years"""
        return round(self._earth_age / self._planet_ratios['jupiter'], 2)

    def on_saturn(self):
        """Converts seconds to Saturn years"""
        return round(self._earth_age / self._planet_ratios['saturn'], 2)

    def on_uranus(self):
        """Converts seconds to Uranus years"""
        return round(self._earth_age / self._planet_ratios['uranus'], 2)

    def on_neptune(self):
        """Converts seconds to Neptune years"""
        return round(self._earth_age / self._planet_ratios['neptune'], 2)