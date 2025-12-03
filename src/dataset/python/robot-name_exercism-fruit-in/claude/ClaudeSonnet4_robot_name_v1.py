from random import choices
from string import ascii_uppercase, digits


class Robot:
    _used_names = set()
    _name_pool = None
    _pool_index = 0
    
    @classmethod
    def _generate_name_pool(cls):
        if cls._name_pool is None:
            # Pre-generate all possible names (26^2 * 10^3 = 676,000 names)
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
        self.reset()

    def reset(self):
        if Robot._name_pool is None:
            Robot._generate_name_pool()
        
        # If we've used all names, reset the used names set
        if len(Robot._used_names) >= len(Robot._name_pool):
            Robot._used_names.clear()
            Robot._pool_index = 0
        
        # Find next unused name efficiently
        while Robot._pool_index < len(Robot._name_pool):
            candidate = Robot._name_pool[Robot._pool_index]
            Robot._pool_index += 1
            
            if candidate not in Robot._used_names:
                self.name = candidate
                Robot._used_names.add(candidate)
                return
        
        # Fallback to random generation if pool is exhausted
        while True:
            self.name = ''.join(
                choices(ascii_uppercase, k=2) + choices(digits, k=3))
            
            if self.name not in Robot._used_names:
                Robot._used_names.add(self.name)
                break