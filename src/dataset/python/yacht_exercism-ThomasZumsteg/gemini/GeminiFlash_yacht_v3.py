from collections import Counter


def count_func(num):
    return lambda dice: num * dice.count(num)


def four_of_a_kind(dice):
    counts = Counter(dice)
    for k, v in counts.items():
        if v >= 4:
            return k * 4
    return 0


def straight(dice):
    if len(set(dice)) != 5:
        return 0
    min_dice = min(dice)
    max_dice = max(dice)
    if max_dice - min_dice == 4:
        return 5
    return 0


# Score categories
# Change the values as you see fit
YACHT = lambda dice: 50 if len(set(dice)) == 1 and len(dice) == 5 else 0
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
CHOICE = lambda dice: sum(dice)


def score(dice, category):
    return category(dice)