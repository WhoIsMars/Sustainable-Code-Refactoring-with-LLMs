def response(hey_bob):
    hey_bob = hey_bob.strip()
    if not hey_bob:
        return "Fine. Be that way!"
    
    question = hey_bob.endswith('?')
    yell = hey_bob.isupper()

    if question and yell:
        return "Calm down, I know what I'm doing!"
    elif question:
        return "Sure."
    elif yell:
        return "Whoa, chill out!"
    else:
        return "Whatever."