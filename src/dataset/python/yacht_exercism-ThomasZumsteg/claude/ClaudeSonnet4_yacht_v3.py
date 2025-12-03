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
    unique_dice = set(dice)
    min_dice = min(unique_dice)
    length = 1
    while min_dice + length in unique_dice:
        length += 1
    return length


def _yacht(dice):
    return 50 if len(set(dice)) == 1 else 0


def _full_house(dice):
    counts = sorted(Counter(dice).values())
    return sum(dice) if counts == [2, 3] else 0


def _little_straight(dice):
    return 30 if straight(dice) == 5 and max(dice) == 5 else 0


def _big_straight(dice):
    return 30 if straight(dice) == 5 and max(dice) == 6 else 0


def _choice(dice):
    return sum(dice)


YACHT = _yacht
ONES = count_func(1)
TWOS = count_func(2)
THREES = count_func(3)
FOURS = count_func(4)
FIVES = count_func(5)
SIXES = count_func(6)
FULL_HOUSE = _full_house
FOUR_OF_A_KIND = four_of_a_kind
LITTLE_STRAIGHT = _little_straight
BIG_STRAIGHT = _big_straight
CHOICE = _choice


def score(dice, category):
    return category(dice)