from random import choices
from string import ascii_uppercase, digits


class Robot:
    _used_names = set()
    _name_pool = None
    _pool_index = 0

    def __init__(self):
        self.name = ''
        self.reset()

    @classmethod
    def _generate_name_pool(cls):
        if cls._name_pool is None:
            cls._name_pool = [
                ''.join([l1, l2, d1, d2, d3])
                for l1 in ascii_uppercase
                for l2 in ascii_uppercase
                for d1 in digits
                for d2 in digits
                for d3 in digits
            ]

    def reset(self):
        if len(self._used_names) >= 676000:
            raise RuntimeError("All possible robot names have been used")
        
        self._generate_name_pool()
        
        while True:
            if self._pool_index >= len(self._name_pool):
                self._pool_index = 0
            
            candidate = self._name_pool[self._pool_index]
            self._pool_index += 1
            
            if candidate not in self._used_names:
                self.name = candidate
                self._used_names.add(candidate)
                break