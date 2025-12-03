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
    
    # Pre-filter house orderings based on Norwegian constraint
    valid_orders = []
    for order in permutations(residents):
        if order[0] == 'Norwegian':
            valid_orders.append(order)
    
    # Pre-filter color arrangements based on constraints
    valid_colors = []
    for colors in permutations(residents):
        red, green, ivory, yellow, blue = colors
        if red == 'Englishman':
            for order in valid_orders:
                if abs(order.index('Norwegian') - order.index(blue)) == 1:
                    try:
                        if order.index(green) - order.index(ivory) == 1:
                            valid_colors.append((colors, order))
                            break
                    except ValueError:
                        continue
    
    # Pre-filter pets based on Spaniard constraint
    valid_pets = []
    for pets in permutations(residents):
        dog, snails, fox, horse, ZEBRA = pets
        if dog == 'Spaniard':
            valid_pets.append(pets)
    
    # Pre-filter drinks based on Ukrainian constraint
    valid_drinks = []
    for drinks in permutations(residents):
        coffee, tea, milk, oj, WATER = drinks
        if tea == 'Ukranian':
            valid_drinks.append(drinks)
    
    # Pre-filter cigarettes based on Japanese constraint
    valid_cigarettes = []
    for cigarettes in permutations(residents):
        OldGold, Kools, Chesterfields, LuckyStrike, Parliaments = cigarettes
        if Parliaments == 'Japanese':
            valid_cigarettes.append(cigarettes)
    
    # Main solving loop with reduced search space
    for colors, order in valid_colors:
        red, green, ivory, yellow, blue = colors
        
        for pets in valid_pets:
            dog, snails, fox, horse, ZEBRA = pets
            
            for drinks in valid_drinks:
                coffee, tea, milk, oj, WATER = drinks
                
                if order.index(milk) != 2:
                    continue
                if coffee != green:
                    continue
                
                for cigarettes in valid_cigarettes:
                    OldGold, Kools, Chesterfields, LuckyStrike, Parliaments = cigarettes
                    
                    if (OldGold == snails and 
                        Kools == yellow and
                        abs(order.index(Chesterfields) - order.index(fox)) == 1 and
                        abs(order.index(Kools) - order.index(horse)) == 1 and
                        LuckyStrike == oj):
                        yield {'zebra': ZEBRA, 'water': WATER}