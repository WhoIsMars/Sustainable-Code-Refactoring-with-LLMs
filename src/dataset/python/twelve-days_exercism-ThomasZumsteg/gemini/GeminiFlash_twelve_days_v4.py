"""Sings the twelve days of christmas"""

def sing():
    """Sings the twelve days of chirstmas"""
    return verses(1, 12)

def verses(start, stop):
    """Sings several verses of the twelve days of christmas"""
    return "\n".join(verse(n) for n in range(start, stop+1)) + "\n"

def verse(v):
    """Sings a verse of the twelve days of christmas"""
    nums = ["first", "second", "third", "fourth", "fifth", "sixth",
            "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth" ]
    gifts = ["a Partridge in a Pear Tree",
             "two Turtle Doves",
             "three French Hens",
             "four Calling Birds",
             "five Gold Rings",
             "six Geese-a-Laying",
             "seven Swans-a-Swimming",
             "eight Maids-a-Milking",
             "nine Ladies Dancing",
             "ten Lords-a-Leaping",
             "eleven Pipers Piping",
             "twelve Drummers Drumming",
            ]
    start = "On the {} day of Christmas my true love gave to me"
    if v == 1:
        return start.format(nums[0]) + ", " + gifts[0] + ".\n"
    else:
        return ", ".join([start.format(nums[v-1])] + gifts[v-1:0:-1] + ["and " + gifts[0]]) + ".\n"