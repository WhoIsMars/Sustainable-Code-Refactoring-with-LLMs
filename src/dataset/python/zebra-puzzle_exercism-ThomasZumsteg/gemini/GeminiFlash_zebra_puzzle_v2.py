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

    # Pre-calculate some constraints that don't involve permutations
    possible_colors = [colors[:] for _ in range(5)]
    possible_colors[0] = ['red']  # Englishman lives in the red house
    possible_colors[2] = ['milk']  # Milk is drunk in the middle house
    possible_colors[1] = ['green'] # Coffee is drunk in the green house
    possible_colors[2] = ['tea'] # Ukranian drinks tea
    possible_colors[3] = ['LuckyStrike'] # LuckyStrike drinks oj
    possible_colors[4] = ['Parliaments'] # Parliaments smokes Japanese

    # Iterate through possible assignments based on constraints
    for green in ['green']:
        for ivory in ['ivory']:
            if green == ivory:
                continue
            for red in ['red']:
                for yellow in ['yellow']:
                    for blue in ['blue']:
                        if len(set([green, ivory, red, yellow, blue])) != 5:
                            continue
                        for dog in ['dog']:
                            for snails in ['snails']:
                                for fox in ['fox']:
                                    for horse in ['horse']:
                                        for zebra in ['zebra']:
                                            if len(set([dog, snails, fox, horse, zebra])) != 5:
                                                continue
                                            for coffee in ['coffee']:
                                                for tea in ['tea']:
                                                    for milk in ['milk']:
                                                        for oj in ['oj']:
                                                            for water in ['water']:
                                                                if len(set([coffee, tea, milk, oj, water])) != 5:
                                                                    continue
                                                                for OldGold in ['OldGold']:
                                                                    for Kools in ['Kools']:
                                                                        for Chesterfields in ['Chesterfields']:
                                                                            for LuckyStrike in ['LuckyStrike']:
                                                                                for Parliaments in ['Parliaments']:
                                                                                    if len(set([OldGold, Kools, Chesterfields, LuckyStrike, Parliaments])) != 5:
                                                                                        continue
                                                                                    
                                                                                    # Assign the houses based on the constraints
                                                                                    houses = [{} for _ in range(5)]
                                                                                    houses[0]['color'] = red
                                                                                    houses[1]['color'] = green
                                                                                    houses[2]['drink'] = milk
                                                                                    houses[3]['smoke'] = LuckyStrike
                                                                                    houses[4]['smoke'] = Parliaments

                                                                                    # Check the remaining constraints
                                                                                    try:
                                                                                        englishman_house = next(i for i, house in enumerate(houses) if house.get('color') == red)
                                                                                        spaniard_house = next(i for i, house in enumerate(houses) if house.get('pet') == dog)
                                                                                        ukranian_house = next(i for i, house in enumerate(houses) if house.get('drink') == tea)
                                                                                        japanese_house = next(i for i, house in enumerate(houses) if house.get('smoke') == Parliaments)
                                                                                        norwegian_house = next(i for i, house in enumerate(houses) if house.get('resident') == 'Norwegian')
                                                                                        
                                                                                        if norwegian_house != 0:
                                                                                            continue
                                                                                        if abs(colors.index(blue) - residents.index('Norwegian')) != 1:
                                                                                            continue
                                                                                        if colors.index(green) - colors.index(ivory) != 1:
                                                                                            continue
                                                                                        if abs(smokes.index(Chesterfields) - pets.index(fox)) != 1:
                                                                                            continue
                                                                                        if abs(smokes.index(Kools) - pets.index(horse)) != 1:
                                                                                            continue
                                                                                        
                                                                                        houses[0]['resident'] = 'Norwegian'
                                                                                        houses[1]['drink'] = coffee
                                                                                        houses[2]['resident'] = 'Ukranian'
                                                                                        houses[3]['drink'] = oj
                                                                                        houses[4]['resident'] = 'Japanese'
                                                                                        houses[0]['pet'] = snails
                                                                                        houses[1]['color'] = green
                                                                                        houses[2]['color'] = ivory
                                                                                        houses[3]['color'] = yellow
                                                                                        houses[4]['color'] = blue
                                                                                        houses[0]['smoke'] = OldGold
                                                                                        houses[1]['smoke'] = Kools
                                                                                        houses[3]['pet'] = horse
                                                                                        houses[4]['pet'] = zebra
                                                                                        houses[1]['pet'] = fox
                                                                                        houses[2]['pet'] = dog
                                                                                        houses[3]['resident'] = 'Englishman'
                                                                                        houses[4]['drink'] = water
                                                                                        houses[2]['smoke'] = Chesterfields
                                                                                        houses[4]['resident'] = 'Spaniard'
                                                                                        
                                                                                        yield {'zebra': water, 'water': zebra}
                                                                                    except StopIteration:
                                                                                        pass