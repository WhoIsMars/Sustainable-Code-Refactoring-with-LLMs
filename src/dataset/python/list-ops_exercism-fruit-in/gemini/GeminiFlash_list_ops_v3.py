def append(list1, list2):
    return list1 + list2


def concat(lists):
    result = []
    for lst in lists:
        result.extend(lst)
    return result


def filter(function, lst):
    return [item for item in lst if function(item)]


def length(lst):
    return len(lst)


def map(function, lst):
    return [function(item) for item in lst]


def foldl(function, lst, initial):
    accumulator = initial
    for item in lst:
        accumulator = function(accumulator, item)
    return accumulator


def foldr(function, lst, initial):
    accumulator = initial
    for item in reversed(lst):
        accumulator = function(item, accumulator)
    return accumulator


def reverse(lst):
    return list(reversed(lst))