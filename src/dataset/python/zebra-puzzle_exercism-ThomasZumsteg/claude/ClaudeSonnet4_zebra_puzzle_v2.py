def solution():
    """Finds solutions to the zebra puzzle"""
    result = zebra_puzzle()
    return ("It is the %s who drinks the water.\n"
        "The %s keeps the zebra." %(result['water'], result['zebra']))

def zebra_puzzle():
    """Finds the solution to the zebra puzzle"""
    residents = ['Englishman', 'Spaniard', 'Ukrainian', 'Japanese', 'Norwegian']
    
    # Pre-filter based on fixed constraints
    # Norwegian is in first house
    # Englishman lives in red house
    # Green house is immediately to the right of ivory house
    # Milk is drunk in middle house
    
    from itertools import permutations
    
    for houses in permutations(residents):
        if houses[0] != 'Norwegian':
            continue
            
        for colors in permutations(['red', 'green', 'ivory', 'yellow', 'blue']):
            # Englishman lives in red house
            if houses[colors.index('red')] != 'Englishman':
                continue
            
            # Green house immediately right of ivory house
            try:
                ivory_pos = colors.index('ivory')
                green_pos = colors.index('green')
                if green_pos - ivory_pos != 1:
                    continue
            except ValueError:
                continue
            
            # Norwegian lives next to blue house
            blue_pos = colors.index('blue')
            if abs(0 - blue_pos) != 1:
                continue
                
            for pets in permutations(['dog', 'snails', 'fox', 'horse', 'zebra']):
                # Spaniard owns dog
                if houses[pets.index('dog')] != 'Spaniard':
                    continue
                    
                for drinks in permutations(['coffee', 'tea', 'milk', 'oj', 'water']):
                    # Milk drunk in middle house
                    if drinks[2] != 'milk':
                        continue
                    
                    # Coffee drunk in green house
                    if drinks[colors.index('green')] != 'coffee':
                        continue
                    
                    # Ukrainian drinks tea
                    if drinks[houses.index('Ukrainian')] != 'tea':
                        continue
                        
                    for cigarettes in permutations(['OldGold', 'Kools', 'Chesterfields', 'LuckyStrike', 'Parliaments']):
                        # Old Gold smoker owns snails
                        if cigarettes[pets.index('snails')] != 'OldGold':
                            continue
                        
                        # Kools smoked in yellow house
                        if cigarettes[colors.index('yellow')] != 'Kools':
                            continue
                        
                        # Chesterfields smoker lives next to fox owner
                        chester_pos = cigarettes.index('Chesterfields')
                        fox_pos = pets.index('fox')
                        if abs(chester_pos - fox_pos) != 1:
                            continue
                        
                        # Kools smoker lives next to horse owner
                        kools_pos = cigarettes.index('Kools')
                        horse_pos = pets.index('horse')
                        if abs(kools_pos - horse_pos) != 1:
                            continue
                        
                        # Lucky Strike smoker drinks orange juice
                        if cigarettes[drinks.index('oj')] != 'LuckyStrike':
                            continue
                        
                        # Japanese smokes Parliaments
                        if cigarettes[houses.index('Japanese')] != 'Parliaments':
                            continue
                        
                        # Found solution
                        zebra_owner = houses[pets.index('zebra')]
                        water_drinker = houses[drinks.index('water')]
                        return {'zebra': zebra_owner, 'water': water_drinker}