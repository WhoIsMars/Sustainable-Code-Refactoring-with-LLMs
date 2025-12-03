"""Calculates age on various planets"""

class SpaceAge:
    """Calculates age on various planets"""
    _earth_year = 31557600  # seconds
    _ratios = {
        "earth": 1.0,
        "mercury": 0.2408467,
        "venus": 0.61519726,
        "mars": 1.8808158,
        "jupiter": 11.862615,
        "saturn": 29.447498,
        "uranus": 84.016846,
        "neptune": 164.79132,
    }

    def __init__(self, seconds):
        """Stores age in seconds"""
        self.seconds = seconds

    def _calculate_age(self, ratio_to_earth):
        """Converts seconds to planet years"""
        return round(self.seconds / (self._earth_year * ratio_to_earth), 2)

    def __getattr__(self, name):
        """Dynamically calculates age for planets"""
        if name.startswith("on_") and name[3:] in self._ratios:
            return lambda: self._calculate_age(self._ratios[name[3:]])
        raise AttributeError(f"'{type(self).__name__}' object has no attribute '{name}'")