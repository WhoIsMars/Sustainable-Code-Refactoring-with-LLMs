class SpaceAge:
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
        self.seconds = seconds

    def __getattr__(self, name):
        if name in self._ratios:
            return lambda: round(self.seconds / (self._earth_year * self._ratios[name]), 2)
        raise AttributeError(f"'{type(self).__name__}' object has no attribute '{name}'")