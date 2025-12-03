from collections import Counter


def count_func(num):
    return lambda dice: num * sum(1 for d in dice if d == num)


def four_of_a_kind(dice):
    for num, count in Counter(dice).items():
        if count >= 4:
            return num * 4
    return 0


def straight(dice):
    dice_set = set(dice)
    return max((len({d + i for i in range(5)} & dice_set) for d in dice_set), default=0)


YACHT = lambda dice: 50 if len(set(dice)) == 1 else 0
ONES = count_func(1)
TWOS = count_func(2)
THREES = count_func(3)
FOURS = count_func(4)
FIVES = count_func(5)
SIXES = count_func(6)
FULL_HOUSE = lambda dice: sum(dice) if sorted(Counter(dice).values()) == [2, 3] else 0
FOUR_OF_A_KIND = four_of_a_kind
LITTLE_STRAIGHT = lambda dice: 30 if set(dice) == {1, 2, 3, 4, 5} else 0
BIG_STRAIGHT = lambda dice: 30 if set(dice) == {2, 3, 4, 5, 6} else 0
CHOICE = sum


def score(dice, category):
    return category(dice)