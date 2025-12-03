_COLORS = [
    "black",
    "brown",
    "red",
    "orange",
    "yellow",
    "green",
    "blue",
    "violet",
    "grey",
    "white",
]

_COLOR_INDEX_MAP = {color: index for index, color in enumerate(_COLORS)}


def color_code(color):
    return _COLOR_INDEX_MAP[color]


def colors():
    return _COLORS