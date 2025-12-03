def solution():
    """Finds solutions to the zebra puzzle"""
    result = zebra_puzzle()
    return ("It is the %s who drinks the water.\n"
        "The %s keeps the zebra." % (result['water'], result['zebra']))

def zebra_puzzle():
    """Finds the solution to the zebra puzzle"""
    residents = ['Englishman', 'Spaniard', 'Ukranian', 'Japanese', 'Norwegian']
    
    # Pre-filter valid house orderings based on Norwegian constraints
    valid_orders = []
    for i in range(5):
        for j in range(5):
            if i != j and abs(i - j) == 1:  # Norwegian and blue house are neighbors
                order = [None] * 5
                order[0] = 'Norwegian'  # Norwegian in first house
                order[j] = 'blue'
                if j != 0:  # blue house not first
                    valid_orders.append((order, j))
    
    # Pre-filter valid color arrangements
    valid_colors = []
    for green_pos in range(1, 5):  # green can't be first (ivory must be left of green)
        ivory_pos = green_pos - 1
        for red_pos in range(5):
            if red_pos not in (green_pos, ivory_pos):
                for yellow_pos in range(5):
                    if yellow_pos not in (red_pos, green_pos, ivory_pos):
                        blue_pos = 5 - sum([red_pos, green_pos, ivory_pos, yellow_pos])
                        if 0 <= blue_pos <= 4:
                            colors = [None] * 5
                            colors[red_pos] = 'Englishman'
                            colors[green_pos] = 'green'
                            colors[ivory_pos] = 'ivory'
                            colors[yellow_pos] = 'yellow'
                            colors[blue_pos] = 'blue'
                            valid_colors.append((colors, red_pos, green_pos, yellow_pos, blue_pos))
    
    for order_template, blue_house in valid_orders:
        for colors, red_pos, green_pos, yellow_pos, blue_pos in valid_colors:
            if blue_house != blue_pos:
                continue
                
            # Build complete order
            order = order_template[:]
            remaining_residents = [r for r in residents if r != 'Norwegian']
            remaining_positions = [i for i in range(5) if i != 0]
            
            # Place Englishman in red house
            if red_pos == 0:
                continue  # Norwegian already in position 0
            order[red_pos] = 'Englishman'
            remaining_residents.remove('Englishman')
            remaining_positions.remove(red_pos)
            
            # Try all arrangements for remaining residents
            from itertools import permutations
            for perm in permutations(remaining_residents):
                final_order = order[:]
                for i, resident in enumerate(perm):
                    final_order[remaining_positions[i]] = resident
                
                # Check pets constraint: Spaniard owns dog
                spaniard_pos = final_order.index('Spaniard')
                
                # Try pet arrangements
                pets = ['dog', 'snails', 'fox', 'horse', 'zebra']
                for pet_perm in permutations(pets):
                    if pet_perm[spaniard_pos] != 'dog':
                        continue
                    
                    # Try drink arrangements
                    drinks = ['coffee', 'tea', 'milk', 'oj', 'water']
                    for drink_perm in permutations(drinks):
                        if drink_perm[2] != 'milk':  # milk in middle house
                            continue
                        if drink_perm[green_pos] != 'coffee':  # coffee in green house
                            continue
                        ukranian_pos = final_order.index('Ukranian')
                        if drink_perm[ukranian_pos] != 'tea':  # Ukranian drinks tea
                            continue
                        
                        # Try cigarette arrangements
                        cigarettes = ['OldGold', 'Kools', 'Chesterfields', 'LuckyStrike', 'Parliaments']
                        for cig_perm in permutations(cigarettes):
                            # Check all cigarette constraints
                            snails_pos = next(i for i, p in enumerate(pet_perm) if p == 'snails')
                            if cig_perm[snails_pos] != 'OldGold':
                                continue
                            if cig_perm[yellow_pos] != 'Kools':
                                continue
                            
                            chesterfields_pos = next(i for i, c in enumerate(cig_perm) if c == 'Chesterfields')
                            fox_pos = next(i for i, p in enumerate(pet_perm) if p == 'fox')
                            if abs(chesterfields_pos - fox_pos) != 1:
                                continue
                            
                            kools_pos = next(i for i, c in enumerate(cig_perm) if c == 'Kools')
                            horse_pos = next(i for i, p in enumerate(pet_perm) if p == 'horse')
                            if abs(kools_pos - horse_pos) != 1:
                                continue
                            
                            lucky_pos = next(i for i, c in enumerate(cig_perm) if c == 'LuckyStrike')
                            if drink_perm[lucky_pos] != 'oj':
                                continue
                            
                            japanese_pos = final_order.index('Japanese')
                            if cig_perm[japanese_pos] != 'Parliaments':
                                continue
                            
                            # Found solution
                            zebra_pos = next(i for i, p in enumerate(pet_perm) if p == 'zebra')
                            water_pos = next(i for i, d in enumerate(drink_perm) if d == 'water')
                            return {
                                'zebra': final_order[zebra_pos],
                                'water': final_order[water_pos]
                            }