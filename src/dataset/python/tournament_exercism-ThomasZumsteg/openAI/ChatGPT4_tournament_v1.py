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

    def calculate_score(team):
        win, loss, draw = results[team]
        return 3 * win + draw

    lines = ['{:30s} | MP |  W |  D |  L |  P'.format('Team')]
    for team in sorted(results, key=lambda team: (-calculate_score(team), team)):
        win, loss, draw = results[team]
        lines.append('{:30s} | {:2} | {:2} | {:2} | {:2} | {:2}'.format(
            team, win + loss + draw, win, draw, loss, calculate_score(team)))
    return '\n'.join(lines)

def _score(*, WIN, LOSS, DRAW):
    return 3 * WIN + DRAW