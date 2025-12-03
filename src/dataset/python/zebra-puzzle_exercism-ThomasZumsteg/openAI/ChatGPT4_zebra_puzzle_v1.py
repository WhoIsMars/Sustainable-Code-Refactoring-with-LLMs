from itertools import permutations

def solution():
    """Finds solutions to the zebra puzzle"""
    solutions = list(zebra_puzzle())
    assert(len(solutions) == 1)
    return ("It is the %s who drinks the water.\n"
        "The %s keeps the zebra." %(solutions[0]['water'], solutions[0]['zebra']))

def zebra_puzzle():
    """Iterator that finds all solutions to the zebra puzzle"""
    residents = 'Englishman, Spaniard, Ukranian, Japanese, Norwegian'.split(', ')
    orderings = permutations(residents)
    first, _, middle, _, _ = (0, 1, 2, 3, 4)

    for order in orderings:
        if order[0] != 'Norwegian':
            continue
        blue = order[1]
        for (red, green, ivory, yellow, _) in permutations(order):
            if red != 'Englishman' or order.index(green) - order.index(ivory) != 1:
                continue
            for (dog, snails, fox, horse, ZEBRA) in permutations(order):
                if dog != 'Spaniard':
                    continue
                for (coffee, tea, milk, oj, WATER) in permutations(order):
                    if order.index(milk) != middle or coffee != green or tea != 'Ukranian':
                        continue
                    for (OldGold, Kools, Chesterfields, LuckyStrike, Parliaments) in permutations(order):
                        if (OldGold != snails or Kools != yellow or
                            abs(order.index(Chesterfields) - order.index(fox)) != 1 or
                            abs(order.index(Kools) - order.index(horse)) != 1 or
                            LuckyStrike != oj or Parliaments != 'Japanese'):
                            continue
                        yield {'zebra': ZEBRA, 'water': WATER}