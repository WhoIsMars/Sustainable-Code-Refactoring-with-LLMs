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
        self._cached_ages = {}

    def on_planet_gen(self, ratio_to_earth):
        """Returns a function that converts seconds into planet years"""
        def on_planet():
            """Converts seconds to planet years"""
            if ratio_to_earth not in self._cached_ages:
                self._cached_ages[ratio_to_earth] = round(
                    self.seconds / (self._earth_year * ratio_to_earth), 2
                )
            return self._cached_ages[ratio_to_earth]
        return on_planet

    def on_earth(self):
        return self.on_planet_gen(self._planet_ratios['earth'])()

    def on_mercury(self):
        return self.on_planet_gen(self._planet_ratios['mercury'])()

    def on_venus(self):
        return self.on_planet_gen(self._planet_ratios['venus'])()

    def on_mars(self):
        return self.on_planet_gen(self._planet_ratios['mars'])()

    def on_jupiter(self):
        return self.on_planet_gen(self._planet_ratios['jupiter'])()

    def on_saturn(self):
        return self.on_planet_gen(self._planet_ratios['saturn'])()

    def on_uranus(self):
        return self.on_planet_gen(self._planet_ratios['uranus'])()

    def on_neptune(self):
        return self.on_planet_gen(self._planet_ratios['neptune'])()