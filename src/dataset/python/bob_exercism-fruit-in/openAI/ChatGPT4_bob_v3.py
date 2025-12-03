def response(hey_bob):
    hey_bob = hey_bob.strip()
    if not hey_bob:
        return "Fine. Be that way!"
    
    is_question = hey_bob.endswith('?')
    is_yell = hey_bob.isupper()
    
    if is_question and is_yell:
        return "Calm down, I know what I'm doing!"
    elif is_question:
        return "Sure."
    elif is_yell:
        return "Whoa, chill out!"
    else:
        return "Whatever."