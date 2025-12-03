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
            names = []
            for c1 in ascii_uppercase:
                for c2 in ascii_uppercase:
                    for d1 in digits:
                        for d2 in digits:
                            for d3 in digits:
                                names.append(c1 + c2 + d1 + d2 + d3)
            cls._name_pool = names

    def __init__(self):
        self.name = ''
        self.reset()

    def reset(self):
        if Robot._name_pool is None:
            Robot._generate_name_pool()
        
        # If we've used all names, we need to fall back to random generation
        if len(Robot._used_names) >= len(Robot._name_pool):
            while True:
                self.name = ''.join(
                    choices(ascii_uppercase, k=2) + choices(digits, k=3))
                if self.name not in Robot._used_names:
                    Robot._used_names.add(self.name)
                    break
        else:
            # Use sequential assignment from pre-generated pool
            while Robot._name_pool[Robot._pool_index] in Robot._used_names:
                Robot._pool_index = (Robot._pool_index + 1) % len(Robot._name_pool)
            
            self.name = Robot._name_pool[Robot._pool_index]
            Robot._used_names.add(self.name)
            Robot._pool_index = (Robot._pool_index + 1) % len(Robot._name_pool)