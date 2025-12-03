"""Sings the twelve days of christmas"""

ORDINALS = ("first", "second", "third", "fourth", "fifth", "sixth",
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
    result = []
    for n in range(start, stop + 1):
        result.append(verse(n))
    result.append("")
    return "\n".join(result)

def verse(v):
    """Sings a verse of the twelve days of christmas"""
    if v == 1:
        return "On the first day of Christmas my true love gave to me, a Partridge in a Pear Tree.\n"
    
    parts = [f"On the {ORDINALS[v-1]} day of Christmas my true love gave to me"]
    parts.extend(GIFTS[i] for i in range(v-1, -1, -1))
    return ", ".join(parts) + ".\n"