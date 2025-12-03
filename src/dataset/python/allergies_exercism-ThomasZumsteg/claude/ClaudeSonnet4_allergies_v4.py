"""Tracks allergies"""

class Allergies(object):
    """Generates and stores allergies from a given score"""

    allergie_list = ('eggs', 'peanuts', 'shellfish', 'strawberries', 
                     'tomatoes', 'chocolate', 'pollen', 'cats')

    def __init__(self, score):
        """Generates a list of allergies from a score"""
        self._score = score & 255
        self.lst = tuple(allergie for i, allergie in enumerate(self.allergie_list)
                        if self._score & (1 << i))

    def is_allergic_to(self, allergie):
        """Tests if allergie is on the list"""
        try:
            return bool(self._score & (1 << self.allergie_list.index(allergie)))
        except ValueError:
            return False