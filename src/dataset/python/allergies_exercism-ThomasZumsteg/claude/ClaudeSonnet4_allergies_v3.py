"""Tracks allergies"""

class Allergies(object):
    """Generates and stores allergies from a given score"""

    allergie_list = ('eggs', 'peanuts', 'shellfish', 'strawberries', 
                     'tomatoes', 'chocolate', 'pollen', 'cats')

    def __init__(self, score):
        """Generates a list of allergies from a score"""
        self._score = score & 0xFF
        self._allergies = None

    @property
    def lst(self):
        if self._allergies is None:
            self._allergies = [allergie for i, allergie in enumerate(self.allergie_list)
                              if self._score & (1 << i)]
        return self._allergies

    def is_allergic_to(self, allergie):
        """Tests if allergie is on the list"""
        try:
            index = self.allergie_list.index(allergie)
            return bool(self._score & (1 << index))
        except ValueError:
            return False