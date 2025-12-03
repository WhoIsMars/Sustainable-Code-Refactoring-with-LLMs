"""Calculates age on various planets"""

class SpaceAge(object):
    """Calculates age on various planets"""
    _earth_year = 31557600
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
        self._earth_years = seconds / self._earth_year

    def on_planet_gen(self, ratio_to_earth):
        """Returns a function that converts seconds into planet years"""
        def on_planet():
            """Converts seconds to planet years"""
            return round(self._earth_years / ratio_to_earth, 2)
        return on_planet

    def on_earth(self):
        return round(self._earth_years, 2)

    def on_mercury(self):
        return round(self._earth_years / self._planet_ratios['mercury'], 2)

    def on_venus(self):
        return round(self._earth_years / self._planet_ratios['venus'], 2)

    def on_mars(self):
        return round(self._earth_years / self._planet_ratios['mars'], 2)

    def on_jupiter(self):
        return round(self._earth_years / self._planet_ratios['jupiter'], 2)

    def on_saturn(self):
        return round(self._earth_years / self._planet_ratios['saturn'], 2)

    def on_uranus(self):
        return round(self._earth_years / self._planet_ratios['uranus'], 2)

    def on_neptune(self):
        return round(self._earth_years / self._planet_ratios['neptune'], 2)