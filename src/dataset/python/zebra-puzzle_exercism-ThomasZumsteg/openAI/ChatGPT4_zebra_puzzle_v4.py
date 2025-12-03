from itertools import permutations

def solution():
    """Finds solutions to the zebra puzzle"""
    solutions = list(zebra_puzzle())
    assert len(solutions) == 1
    return ("It is the %s who drinks the water.\n"
            "The %s keeps the zebra." % (solutions[0]['water'], solutions[0]['zebra']))

def zebra_puzzle():
    """Iterator that finds all solutions to the zebra puzzle"""
    residents = 'Englishman, Spaniard, Ukranian, Japanese, Norwegian'.split(', ')
    first, _, middle, _, _ = (0, 1, 2, 3, 4)

    for order in permutations(residents):
        if order[0] != 'Norwegian':
            continue
        blue = order.index('Norwegian') + 1 if order.index('Norwegian') + 1 < 5 else order.index('Norwegian') - 1
        if order[blue] != 'Norwegian':
            continue

        for (red, green, ivory, yellow, blue_house) in permutations(order):
            if red != 'Englishman' or green != order[order.index(ivory) + 1]:
                continue

            for (dog, snails, fox, horse, zebra) in permutations(order):
                if dog != 'Spaniard':
                    continue

                for (coffee, tea, milk, oj, water) in permutations(order):
                    if coffee != green or tea != 'Ukranian' or order[middle] != milk:
                        continue

                    for (OldGold, Kools, Chesterfields, LuckyStrike, Parliaments) in permutations(order):
                        if (OldGold != snails or Kools != yellow or
                                abs(order.index(Chesterfields) - order.index(fox)) != 1 or
                                abs(order.index(Kools) - order.index(horse)) != 1 or
                                LuckyStrike != oj or Parliaments != 'Japanese'):
                            continue

                        yield {'zebra': zebra, 'water': water}