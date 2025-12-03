def response(hey_bob):
    stripped = hey_bob.strip()
    if not stripped:
        return "Fine. Be that way!"
    
    question = stripped.endswith('?')
    yell = stripped.isupper()

    if question and yell:
        return "Calm down, I know what I'm doing!"
    elif question:
        return "Sure."
    elif yell:
        return "Whoa, chill out!"
    else:
        return "Whatever."