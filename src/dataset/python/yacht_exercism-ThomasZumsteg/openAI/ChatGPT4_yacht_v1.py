from collections import Counter


def count_func(num):
    return lambda dice: num * sum(1 for d in dice if d == num)


def four_of_a_kind(dice):
    for k, v in Counter(dice).items():
        if v >= 4:
            return k * 4
    return 0


def straight(dice):
    dice_set = set(dice)
    return 5 if all(n in dice_set for n in range(min(dice), min(dice) + 5)) else 0


# Score categories
YACHT = lambda dice: 50 if len(set(dice)) == 1 and len(dice) == 5 else 0
ONES = count_func(1)
TWOS = count_func(2)
THREES = count_func(3)
FOURS = count_func(4)
FIVES = count_func(5)
SIXES = count_func(6)
FULL_HOUSE = lambda dice: sum(dice) if sorted(Counter(dice).values()) == [2, 3] else 0
FOUR_OF_A_KIND = four_of_a_kind
LITTLE_STRAIGHT = lambda dice: 30 if straight(dice) and max(dice) == 5 else 0
BIG_STRAIGHT = lambda dice: 30 if straight(dice) and max(dice) == 6 else 0
CHOICE = sum


def score(dice, category):
    return category(dice)