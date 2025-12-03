def append(list1, list2):
    result = list1[:]
    result.extend(list2)
    return result


def concat(lists):
    result = []
    for lst in lists:
        result.extend(lst)
    return result


def filter(function, list):
    return [item for item in list if function(item)]


def length(list):
    return len(list)


def map(function, list):
    return [function(item) for item in list]


def foldl(function, list, initial):
    result = initial
    for item in list:
        result = function(result, item)
    return result


def foldr(function, list, initial):
    result = initial
    for item in reversed(list):
        result = function(item, result)
    return result


def reverse(list):
    return list[::-1]