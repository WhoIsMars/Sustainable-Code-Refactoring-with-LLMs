"""Sings the twelve days of christmas"""

NUMS = ("first", "second", "third", "fourth", "fifth", "sixth",
        "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth")

GIFTS = ("and a Partridge in a Pear Tree",
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
         "twelve Drummers Drumming")

FIRST_VERSE = "On the first day of Christmas my true love gave to me, a Partridge in a Pear Tree.\n"

def sing():
    """Sings the twelve days of chirstmas"""
    return verses(1, 12)

def verses(start, stop):
    """Sings several verses of the twelve days of christmas"""
    result = []
    for n in range(start, stop + 1):
        result.append(verse(n))
    result.append("")
    return "\n".join(result)

def verse(v):
    """Sings a verse of the twelve days of christmas"""
    if v == 1:
        return FIRST_VERSE
    
    verse_parts = [f"On the {NUMS[v-1]} day of Christmas my true love gave to me"]
    verse_parts.extend(GIFTS[i] for i in range(v-1, -1, -1))
    return ", ".join(verse_parts) + ".\n"