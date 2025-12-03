from collections import defaultdict

WIN, LOSS, DRAW = 'WIN', 'LOSS', 'DRAW'


def tally(tournament_results):
    results = defaultdict(lambda: {WIN: 0, LOSS: 0, DRAW: 0})
    for line in tournament_results.splitlines():
        if not line:
            continue
        home, away, result = line.split(';')
        if result == 'win':
            results[home][WIN] += 1
            results[away][LOSS] += 1
        elif result == 'loss':
            results[home][LOSS] += 1
            results[away][WIN] += 1
        else:  # result == 'draw':
            results[home][DRAW] += 1
            results[away][DRAW] += 1

    team_data = []
    for team, scores in results.items():
        mp = sum(scores.values())
        w = scores[WIN]
        d = scores[DRAW]
        l = scores[LOSS]
        p = 3 * w + d
        team_data.append((team, mp, w, d, l, p))

    lines = ['{:30s} | MP |  W |  D |  L |  P'.format('Team')]
    for team, mp, w, d, l, p in sorted(team_data, key=lambda x: (-x[5], x[0])):
        lines.append('{:30s} | {:2} | {:2} | {:2} | {:2} | {:2}'.format(team, mp, w, d, l, p))

    return '\n'.join(lines)