from random import choices
from string import ascii_uppercase, digits


class Robot:
    _used_names = set()
    _name_pool = None
    _pool_index = 0
    
    @classmethod
    def _generate_name_pool(cls):
        if cls._name_pool is None:
            cls._name_pool = [
                f"{c1}{c2}{d1}{d2}{d3}"
                for c1 in ascii_uppercase
                for c2 in ascii_uppercase
                for d1 in digits
                for d2 in digits
                for d3 in digits
            ]
    
    def __init__(self):
        self.name = ''
        self._generate_name_pool()
        self.reset()

    def reset(self):
        if len(self._used_names) >= len(self._name_pool):
            raise RuntimeError("All possible names have been used")
        
        while True:
            if self._pool_index >= len(self._name_pool):
                self._pool_index = 0
            
            candidate = self._name_pool[self._pool_index]
            self._pool_index += 1
            
            if candidate not in self._used_names:
                self.name = candidate
                self._used_names.add(candidate)
                break