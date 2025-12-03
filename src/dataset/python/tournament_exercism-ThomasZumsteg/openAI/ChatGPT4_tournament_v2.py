from collections import defaultdict

WIN, LOSS, DRAW = 'WIN', 'LOSS', 'DRAW'

def tally(tournament_results):
    results = defaultdict(lambda: [0, 0, 0])  # Use list for less memory overhead
    for line in tournament_results.splitlines():
        home, away, result = line.split(';')
        if result == 'win':
            results[home][0] += 1  # WIN
            results[away][1] += 1  # LOSS
        elif result == 'loss':
            results[home][1] += 1  # LOSS
            results[away][0] += 1  # WIN
        elif result == 'draw':
            results[home][2] += 1  # DRAW
            results[away][2] += 1  # DRAW
    lines = ['{:30s} | MP |  W |  D |  L |  P'.format('Team')]
    for team in sorted(results, key=lambda team: (-_score(*results[team]), team)):
        wins, losses, draws = results[team]
        matches_played = wins + losses + draws
        points = _score(wins, losses, draws)
        lines.append(f'{team:30s} | {matches_played:2} | {wins:2} | {draws:2} | {losses:2} | {points:2}')
    return '\n'.join(lines)

def _score(wins, losses, draws):
    return 3 * wins + draws