"""Calculates age on various planets"""

class SpaceAge:
    """Calculates age on various planets"""
    _earth_year = 31557600  # seconds
    _ratios = {
        "on_earth": 1.0,
        "on_mercury": 0.2408467,
        "on_venus": 0.61519726,
        "on_mars": 1.8808158,
        "on_jupiter": 11.862615,
        "on_saturn": 29.447498,
        "on_uranus": 84.016846,
        "on_neptune": 164.79132,
    }

    def __init__(self, seconds):
        """Stores age and precomputes planet ages"""
        self.seconds = seconds
        self._ages = {
            name: round(self.seconds / (self._earth_year * ratio), 2)
            for name, ratio in self._ratios.items()
        }

    def __getattr__(self, name):
        """Dynamically returns precomputed planet age"""
        if name in self._ages:
            return lambda: self._ages[name]
        raise AttributeError(f"'{type(self).__name__}' object has no attribute '{name}'")