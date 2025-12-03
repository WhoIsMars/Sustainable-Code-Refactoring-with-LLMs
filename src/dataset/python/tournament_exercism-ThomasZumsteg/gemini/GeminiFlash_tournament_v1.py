from collections import defaultdict

WIN, LOSS, DRAW = 'WIN', 'LOSS', 'DRAW'


def tally(tournament_results):
    results = defaultdict(lambda: [0, 0, 0])  # [WIN, DRAW, LOSS]
    for line in tournament_results.splitlines():
        if not line:
            continue
        home, away, result = line.split(';')
        if result == 'win':
            results[home][0] += 1
            results[away][2] += 1
        elif result == 'loss':
            results[home][2] += 1
            results[away][0] += 1
        else:  # result == 'draw'
            results[home][1] += 1
            results[away][1] += 1

    team_data = []
    for team, scores in results.items():
        wins, draws, losses = scores
        points = 3 * wins + draws
        team_data.append((team, wins + draws + losses, wins, draws, losses, points))

    lines = ['{:30s} | MP |  W |  D |  L |  P'.format('Team')]
    team_data.sort(key=lambda x: (-x[5], x[0]))  # Sort by points (descending) then team name (ascending)

    for team, matches_played, wins, draws, losses, points in team_data:
        lines.append('{:30s} | {:2} | {:2} | {:2} | {:2} | {:2}'.format(
            team, matches_played, wins, draws, losses, points))

    return '\n'.join(lines)