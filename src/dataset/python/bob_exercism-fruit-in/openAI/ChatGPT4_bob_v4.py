def response(hey_bob):
    stripped = hey_bob.strip()
    if not stripped:
        return "Fine. Be that way!"
    is_question = stripped.endswith('?')
    is_yell = stripped.isupper()
    if is_question and is_yell:
        return "Calm down, I know what I'm doing!"
    if is_question:
        return "Sure."
    if is_yell:
        return "Whoa, chill out!"
    return "Whatever."