"""Sings the twelve days of christmas"""

# Pre-computed constants to avoid repeated list creation
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

def sing():
    """Sings the twelve days of chirstmas"""
    return verses(1, 12)

def verses(start, stop):
    """Sings several verses of the twelve days of christmas"""
    return "\n".join(verse(n) for n in range(start, stop+1)) + "\n"

def verse(v):
    """Sings a verse of the twelve days of christmas"""
    if v == 1:
        return "On the first day of Christmas my true love gave to me, a Partridge in a Pear Tree.\n"
    
    return f"On the {NUMS[v-1]} day of Christmas my true love gave to me, " + ", ".join(GIFTS[v-1::-1]) + ".\n"