def response(hey_bob):
    stripped = hey_bob.strip()
    
    if not stripped:
        return "Fine. Be that way!"
    
    question = hey_bob.rstrip().endswith('?')
    
    has_alpha = False
    has_upper = False
    has_lower = False
    
    for c in hey_bob:
        if c.isalpha():
            has_alpha = True
            if c.isupper():
                has_upper = True
            else:
                has_lower = True
            if has_upper and has_lower:
                break
    
    yell = has_alpha and has_upper and not has_lower
    
    if question and yell:
        return "Calm down, I know what I'm doing!"
    elif question:
        return "Sure."
    elif yell:
        return "Whoa, chill out!"
    else:
        return "Whatever."