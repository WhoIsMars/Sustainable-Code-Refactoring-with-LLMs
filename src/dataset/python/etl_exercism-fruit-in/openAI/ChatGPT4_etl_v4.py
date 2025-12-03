def transform(legacy_data):
    return dict((letter.lower(), points) for points, letters in legacy_data.items() for letter in letters)