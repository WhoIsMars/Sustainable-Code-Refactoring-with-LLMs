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
    dice_set = set(dice)
    min_dice = min(dice_set)
    length = 1
    while min_dice + length in dice_set:
        length += 1
    return length


# Score categories
YACHT = lambda dice: 50 if len(set(dice)) == 1 else 0
ONES = count_func(1)
TWOS = count_func(2)
THREES = count_func(3)
FOURS = count_func(4)
FIVES = count_func(5)
SIXES = count_func(6)
FULL_HOUSE = lambda dice: sum(dice) if \
    sorted(Counter(dice).values()) == [2, 3] else 0
FOUR_OF_A_KIND = four_of_a_kind
LITTLE_STRAIGHT = lambda dice: 30 if straight(dice) == 5 and max(dice) == 5 else 0
BIG_STRAIGHT = lambda dice: 30 if straight(dice) == 5 and max(dice) == 6 else 0
CHOICE = sum


def score(dice, category):
    return category(dice)