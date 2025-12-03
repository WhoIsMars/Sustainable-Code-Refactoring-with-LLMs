"""Tracks allergies"""

class Allergies(object):
    """Generates and stores allergies from a given score"""

    allergen_map = {
        1: 'eggs',
        2: 'peanuts',
        4: 'shellfish',
        8: 'strawberries',
        16: 'tomatoes',
        32: 'chocolate',
        64: 'pollen',
        128: 'cats'
    }

    def __init__(self, score):
        """Generates a list of allergies from a score"""
        self.lst = []
        remaining_score = score % 256  # Only consider scores within the range
        for value, allergen in Allergies.allergen_map.items():
            if remaining_score >= value:
                self.lst.append(allergen)
                remaining_score -= value
        self.lst.reverse()  # Maintain original order

    def is_allergic_to(self, allergie):
        """Tests if allergie is on the list"""
        return allergie in self.lst