from collections import defaultdict

WIN, LOSS, DRAW = 'WIN', 'LOSS', 'DRAW'

def tally(tournament_results):
    results = defaultdict(lambda: [0, 0, 0])  # [WIN, LOSS, DRAW]
    
    for line in tournament_results.splitlines():
        home, away, result = line.split(';')
        if result == 'win':
            results[home][0] += 1
            results[away][1] += 1
        elif result == 'loss':
            results[home][1] += 1
            results[away][0] += 1
        elif result == 'draw':
            results[home][2] += 1
            results[away][2] += 1
    
    # Pre-calculate scores and sort data
    team_data = []
    for team, stats in results.items():
        score = 3 * stats[0] + stats[2]
        team_data.append((-score, team, stats))
    
    team_data.sort()
    
    lines = ['Team                           | MP |  W |  D |  L |  P']
    for _, team, stats in team_data:
        mp = stats[0] + stats[1] + stats[2]
        score = 3 * stats[0] + stats[2]
        lines.append(f'{team:30s} | {mp:2} | {stats[0]:2} | {stats[2]:2} | {stats[1]:2} | {score:2}')
    
    return '\n'.join(lines)

def _score(*, WIN, LOSS, DRAW):
    return 3 * WIN + DRAW