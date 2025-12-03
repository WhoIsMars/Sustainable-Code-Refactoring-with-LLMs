def transform(legacy_data):
    transformed_data = {}
    for points, letters in legacy_data.items():
        for letter in letters:
            transformed_data[letter.lower()] = points
    return transformed_data