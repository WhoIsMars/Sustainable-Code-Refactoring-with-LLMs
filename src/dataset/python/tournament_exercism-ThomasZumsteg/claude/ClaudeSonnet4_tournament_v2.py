from collections import defaultdict

WIN, LOSS, DRAW = 'WIN', 'LOSS', 'DRAW'

def tally(tournament_results):
    results = defaultdict(lambda: [0, 0, 0])  # [WIN, DRAW, LOSS]
    
    for line in tournament_results.splitlines():
        home, away, result = line.split(';')
        if result == 'win':
            results[home][0] += 1
            results[away][2] += 1
        elif result == 'loss':
            results[home][2] += 1
            results[away][0] += 1
        else:  # draw
            results[home][1] += 1
            results[away][1] += 1
    
    # Pre-calculate scores and sort
    team_data = []
    for team, stats in results.items():
        score = 3 * stats[0] + stats[1]
        mp = sum(stats)
        team_data.append((-score, team, mp, stats[0], stats[1], stats[2], score))
    
    team_data.sort()
    
    lines = ['Team                           | MP |  W |  D |  L |  P']
    for _, team, mp, wins, draws, losses, score in team_data:
        lines.append(f'{team:30s} | {mp:2} | {wins:2} | {draws:2} | {losses:2} | {score:2}')
    
    return '\n'.join(lines)

def _score(*, WIN, LOSS, DRAW):
    return 3 * WIN + DRAW