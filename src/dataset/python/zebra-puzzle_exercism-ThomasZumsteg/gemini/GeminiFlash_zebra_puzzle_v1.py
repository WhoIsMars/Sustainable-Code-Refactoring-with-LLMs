def solution():
    """Finds solutions to the zebra puzzle"""
    solutions = list(zebra_puzzle())
    assert(len(solutions) == 1)
    return ("It is the %s who drinks the water.\n"
        "The %s keeps the zebra." %(solutions[0]['water'], solutions[0]['zebra']))

def zebra_puzzle():
    """Iterator that finds all solutions to the zebra puzzle"""
    residents = ['Englishman', 'Spaniard', 'Ukranian', 'Japanese', 'Norwegian']
    
    for red in ['Englishman']:
        for blue in [residents[i] for i in range(len(residents))]:
            for norwegian in ['Norwegian']:
                if abs(residents.index(norwegian) - residents.index(blue)) != 1 and residents.index(norwegian) != 0:
                    continue
                if residents.index(norwegian) != 0 and abs(residents.index(norwegian) - residents.index(blue)) != 1:
                    continue
                for green in [residents[i] for i in range(len(residents))]:
                    for ivory in [residents[i] for i in range(len(residents))]:
                        if residents.index(green) - residents.index(ivory) != 1:
                            continue
                        for dog in ['Spaniard']:
                            for milk in [residents[2]]:
                                for coffee in [green]:
                                    for tea in ['Ukranian']:
                                        for snails in [residents[i] for i in range(len(residents))]:
                                            for yellow in [residents[i] for i in range(len(residents))]:
                                                for chesterfields in [residents[i] for i in range(len(residents))]:
                                                    for fox in [residents[i] for i in range(len(residents))]:
                                                        if abs(residents.index(chesterfields) - residents.index(fox)) != 1:
                                                            continue
                                                        for horse in [residents[i] for i in range(len(residents))]:
                                                            if abs(residents.index(yellow) - residents.index(horse)) != 1:
                                                                continue
                                                            for luckystrike in [residents[i] for i in range(len(residents))]:
                                                                for parliaments in ['Japanese']:
                                                                    for water in [residents[i] for i in range(len(residents))]:
                                                                        for zebra in [residents[i] for i in range(len(residents))]:
                                                                            
                                                                            assignments = {
                                                                                red: 'red',
                                                                                blue: 'blue',
                                                                                norwegian: 'norwegian',
                                                                                green: 'green',
                                                                                ivory: 'ivory',
                                                                                dog: 'dog',
                                                                                milk: 'milk',
                                                                                coffee: 'coffee',
                                                                                tea: 'tea',
                                                                                snails: 'snails',
                                                                                yellow: 'yellow',
                                                                                chesterfields: 'chesterfields',
                                                                                fox: 'fox',
                                                                                horse: 'horse',
                                                                                luckystrike: 'luckystrike',
                                                                                parliaments: 'parliaments',
                                                                                water: 'water',
                                                                                zebra: 'zebra'
                                                                            }

                                                                            
                                                                            if len(set(assignments.keys())) == len(residents):
                                                                                yield { 'zebra': zebra, 'water': water }