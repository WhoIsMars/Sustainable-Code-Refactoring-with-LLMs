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
    lines = ['{:<30} | MP |  W |  D |  L |  P'.format('Team')]
    for team in sorted(results, key=lambda team: (-_score(*results[team]), team)):
        wins, losses, draws = results[team]
        matches_played = wins + losses + draws
        points = _score(wins, losses, draws)
        lines.append(f'{team:<30} | {matches_played:2} | {wins:2} | {draws:2} | {losses:2} | {points:2}')
    return '\n'.join(lines)

def _score(WIN, LOSS, DRAW):
    return 3 * WIN + DRAW