from collections import defaultdict

WIN, LOSS, DRAW = 'WIN', 'LOSS', 'DRAW'

def tally(tournament_results):
    results = defaultdict(lambda: [0, 0, 0])
    for line in tournament_results.splitlines():
        if not line:
            continue
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

    team_data = []
    for team, scores in results.items():
        w, l, d = scores
        mp = w + l + d
        p = 3 * w + d
        team_data.append((team, mp, w, d, l, p))

    lines = ['{:30s} | MP |  W |  D |  L |  P'.format('Team')]
    for team, mp, w, d, l, p in sorted(team_data, key=lambda x: (-x[5], x[0])):
        lines.append('{:30s} | {:2} | {:2} | {:2} | {:2} | {:2}'.format(team, mp, w, d, l, p))

    return '\n'.join(lines)