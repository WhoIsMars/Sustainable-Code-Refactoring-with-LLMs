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
        128: 'cats',
    }

    def __init__(self, score):
        """Generates a list of allergies from a score"""
        self.lst = []
        remaining_score = score
        for value in sorted(Allergies.allergen_map.keys(), reverse=True):
            if remaining_score >= value:
                self.lst.append(Allergies.allergen_map[value])
                remaining_score -= value
        self.lst.reverse()


    def is_allergic_to(self, allergie):
        """Tests if allergie is on the list"""
        return allergie in self.lst