def solution():
    """Finds solutions to the zebra puzzle"""
    result = zebra_puzzle()
    return ("It is the %s who drinks the water.\n"
        "The %s keeps the zebra." %(result['water'], result['zebra']))

def zebra_puzzle():
    """Finds the solution to the zebra puzzle"""
    residents = ['Englishman', 'Spaniard', 'Ukranian', 'Japanese', 'Norwegian']
    
    # Pre-filter based on fixed constraints
    # Norwegian is in first house
    # Englishman lives in red house
    # Milk is drunk in middle house (index 2)
    # Green house is immediately to the right of ivory house
    # Blue house is next to Norwegian house (so blue must be in position 1)
    
    # Since Norwegian is first and blue is next to Norwegian, blue is second
    # Green is right of ivory, so possible positions: (0,1), (1,2), (2,3), (3,4)
    # But position 1 is blue, so green can't be position 1
    # If ivory=0, green=1 (impossible, blue is there)
    # If ivory=1, green=2 (impossible, blue is position 1)
    # If ivory=2, green=3 (possible)
    # If ivory=3, green=4 (possible)
    
    for ivory_pos in [2, 3]:
        green_pos = ivory_pos + 1
        
        # Determine remaining color positions
        colors = [''] * 5
        colors[0] = 'red'  # Englishman in red, and we'll verify Norwegian isn't Englishman
        colors[1] = 'blue'
        colors[ivory_pos] = 'ivory'
        colors[green_pos] = 'green'
        
        # Find yellow position
        yellow_pos = next(i for i in range(5) if colors[i] == '')
        colors[yellow_pos] = 'yellow'
        
        # Try different arrangements of residents
        for positions in generate_valid_arrangements():
            if positions[0] != 'Norwegian':
                continue
            if colors[positions.index('Englishman')] != 'red':
                continue
                
            # Check drinks
            drinks = [''] * 5
            drinks[2] = 'milk'  # Middle house drinks milk
            drinks[green_pos] = 'coffee'  # Green house drinks coffee
            drinks[positions.index('Ukranian')] = 'tea'  # Ukranian drinks tea
            
            # Try pets and cigarettes
            for pets_config in generate_pet_configs(positions):
                for cig_config in generate_cigarette_configs(positions, colors, pets_config):
                    # Fill remaining drinks
                    remaining_drinks = ['oj', 'water']
                    drink_positions = [i for i in range(5) if drinks[i] == '']
                    
                    for i, pos in enumerate(drink_positions):
                        drinks[pos] = remaining_drinks[i]
                    
                    # Verify Lucky Strike drinks OJ
                    lucky_pos = next((i for i in range(5) if cig_config[i] == 'LuckyStrike'), -1)
                    if lucky_pos != -1 and drinks[lucky_pos] == 'oj':
                        water_pos = drinks.index('water')
                        zebra_pos = pets_config.index('zebra')
                        return {'water': positions[water_pos], 'zebra': positions[zebra_pos]}

def generate_valid_arrangements():
    """Generate valid resident arrangements"""
    residents = ['Englishman', 'Spaniard', 'Ukranian', 'Japanese', 'Norwegian']
    from itertools import permutations
    return permutations(residents)

def generate_pet_configs(positions):
    """Generate valid pet configurations"""
    pets = ['dog', 'snails', 'fox', 'horse', 'zebra']
    from itertools import permutations
    
    spaniard_pos = positions.index('Spaniard')
    
    for config in permutations(pets):
        if config[spaniard_pos] == 'dog':  # Spaniard owns dog
            yield config

def generate_cigarette_configs(positions, colors, pets):
    """Generate valid cigarette configurations"""
    cigarettes = ['OldGold', 'Kools', 'Chesterfields', 'LuckyStrike', 'Parliaments']
    from itertools import permutations
    
    japanese_pos = positions.index('Japanese')
    yellow_pos = colors.index('yellow')
    snails_pos = pets.index('snails')
    fox_pos = pets.index('fox')
    horse_pos = pets.index('horse')
    
    for config in permutations(cigarettes):
        if (config[japanese_pos] == 'Parliaments' and  # Japanese smokes Parliaments
            config[yellow_pos] == 'Kools' and  # Kools in yellow house
            config[snails_pos] == 'OldGold' and  # OldGold owner keeps snails
            abs(config.index('Chesterfields') - fox_pos) == 1 and  # Chesterfields next to fox
            abs(config.index('Kools') - horse_pos) == 1):  # Kools next to horse
            yield config