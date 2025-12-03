"""Tracks allergies"""

class Allergies(object):
    """Generates and stores allergies from a given score"""

                   # Allergie       # score
    allergie_list = ['eggs',        # 1
                     'peanuts',     # 2
                     'shellfish',   # 4
                     'strawberries',# 8
                     'tomatoes',    # 16
                     'chocolate',   # 32
                     'pollen',      # 64
                     'cats',        # 128
                    ]

    def __init__(self, score):
        """Generates a list of allergies from a score"""
        self.score = score & 255  # Mask to only consider valid bits
        self.lst = None

    def _get_allergies(self):
        """Lazy initialization of allergies list"""
        if self.lst is None:
            self.lst = [allergie
                        for i, allergie in enumerate(Allergies.allergie_list)
                        if self.score & (1 << i)]
        return self.lst

    def is_allergic_to(self, allergie):
        """Tests if allergie is on the list"""
        try:
            index = Allergies.allergie_list.index(allergie)
            return bool(self.score & (1 << index))
        except ValueError:
            return False

    @property
    def lst(self):
        return self._lst

    @lst.setter
    def lst(self, value):
        self._lst = value

    @lst.getter
    def lst(self):
        return self._get_allergies()