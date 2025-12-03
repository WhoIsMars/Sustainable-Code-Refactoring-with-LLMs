"""Sings the twelve days of christmas"""

def sing():
    """Sings the twelve days of chirstmas"""
    return verses(1, 12)

def verses(start, stop):
    """Sings several verses of the twelve days of christmas"""
    all_verses = []
    for n in range(start, stop + 1):
        all_verses.append(verse(n))
    return "\n".join(all_verses) + "\n"

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

    start = "On the %s day of Christmas my true love gave to me, " % nums[v-1]
    
    if v == 1:
        return start + gifts[0] + ".\n"

    gifts_for_verse = gifts[v-1::-1]
    gifts_string = ", ".join(gifts_for_verse[:-1]) + ", and " + gifts_for_verse[-1]
    return start + gifts_string + ".\n"