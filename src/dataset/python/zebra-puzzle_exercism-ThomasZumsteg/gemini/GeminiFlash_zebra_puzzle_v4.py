from itertools import permutations

def solution():
    """Finds solutions to the zebra puzzle"""
    solutions = list(zebra_puzzle())
    assert(len(solutions) == 1)
    return ("It is the %s who drinks the water.\n"
        "The %s keeps the zebra." %(solutions[0]['water'], solutions[0]['zebra']))

def zebra_puzzle():
    """Iterator that finds all solutions to the zebra puzzle"""
    residents = ['Englishman', 'Spaniard', 'Ukranian', 'Japanese', 'Norwegian']
    colors = ['red', 'green', 'ivory', 'yellow', 'blue']
    pets = ['dog', 'snails', 'fox', 'horse', 'zebra']
    drinks = ['coffee', 'tea', 'milk', 'oj', 'water']
    smokes = ['OldGold', 'Kools', 'Chesterfields', 'LuckyStrike', 'Parliaments']

    for red, green, ivory, yellow, blue in permutations(colors):
        if red != 'Englishman':
            continue

        if abs(colors.index('Norwegian') - colors.index(blue)) != 1:
            continue

        if colors[0] != 'Norwegian':
            continue

        if colors.index(green) - colors.index(ivory) != 1:
            continue

        for dog, snails, fox, horse, zebra in permutations(pets):
            if dog != 'Spaniard':
                continue

            for coffee, tea, milk, oj, water in permutations(drinks):
                if drinks.index(milk) != 2:
                    continue

                if coffee != green:
                    continue

                if tea != 'Ukranian':
                    continue

                for OldGold, Kools, Chesterfields, LuckyStrike, Parliaments in permutations(smokes):
                    if OldGold != snails:
                        continue

                    if Kools != yellow:
                        continue

                    if abs(smokes.index(Chesterfields) - pets.index(fox)) != 1:
                        continue

                    if abs(smokes.index(Kools) - pets.index(horse)) != 1:
                        continue

                    if LuckyStrike != oj:
                        continue

                    if Parliaments != 'Japanese':
                        continue

                    yield {'zebra': zebra, 'water': water}