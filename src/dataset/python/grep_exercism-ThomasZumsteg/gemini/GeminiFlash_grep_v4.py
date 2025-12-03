def grep(pattern, files, flags=''):
    matches = []
    for file_name in files:
        file_matches = []
        try:
            with open(file_name, 'r') as f:
                for l, line in enumerate(f, 1):
                    if match(pattern, line, flags):
                        file_matches.append((l, line))
                        if 'l' in flags:
                            break
        except FileNotFoundError:
            continue  # Or handle the error as needed
        matches.append((file_name, file_matches))
    return formatter(matches, flags)

def match(pattern, line, flags):
    if 'i' in flags:
        pattern = pattern.lower()
        line = line.lower()

    if 'x' in flags:
        return pattern == line.strip()
    elif 'v' in flags:
        return pattern not in line
    else:
        return pattern in line

def formatter(matches, flags):
    output = []
    filename_prefix = len(matches) > 1 and 'l' not in flags

    for filename, lines in matches:
        if 'l' in flags and lines:
            output.append(f'{filename}\n')
            continue

        for ln, line in lines:
            if 'n' in flags:
                line_format = f'{filename}:' if filename_prefix else ''
                output.append(f'{line_format}{ln}:{line}')
            else:
                line_format = f'{filename}:' if filename_prefix else ''
                output.append(f'{line_format}{line}')

    return ''.join(output)