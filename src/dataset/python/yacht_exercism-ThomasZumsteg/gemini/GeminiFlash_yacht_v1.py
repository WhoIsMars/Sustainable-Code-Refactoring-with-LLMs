from collections import Counter


def count_func(num):
    def counter(dice):
        count = 0
        for die in dice:
            if die == num:
                count += 1
        return num * count

    return counter


def four_of_a_kind(dice):
    counts = {}
    for die in dice:
        if die in counts:
            counts[die] += 1
        else:
            counts[die] = 1
        if counts[die] >= 4:
            return die * 4
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
def yacht(dice):
    if len(dice) == 5:
        first = dice[0]
        for die in dice:
            if die != first:
                return 0
        return 50
    return 0


ONES = count_func(1)
TWOS = count_func(2)
THREES = count_func(3)
FOURS = count_func(4)
FIVES = count_func(5)
SIXES = count_func(6)


def full_house(dice):
    counts = {}
    for die in dice:
        if die in counts:
            counts[die] += 1
        else:
            counts[die] = 1

    if len(counts) == 2:
        values = sorted(counts.values())
        if values == [2, 3]:
            return sum(dice)
    return 0


FOUR_OF_A_KIND = four_of_a_kind


def little_straight(dice):
    if len(set(dice)) == 5 and max(dice) == 5 and min(dice) == 1:
        return 30
    return 0


def big_straight(dice):
    if len(set(dice)) == 5 and max(dice) == 6 and min(dice) == 2:
        return 30
    return 0


def choice(dice):
    total = 0
    for die in dice:
        total += die
    return total


YACHT = yacht
LITTLE_STRAIGHT = little_straight
BIG_STRAIGHT = big_straight
CHOICE = choice
FULL_HOUSE = full_house


def score(dice, category):
    return category(dice)