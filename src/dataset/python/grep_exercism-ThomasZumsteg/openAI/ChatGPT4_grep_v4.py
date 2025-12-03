def grep(pattern, files, flags=''):
    matches = []
    for file_name in files:
        with open(file_name) as file:
            file_matches = []
            for l, line in enumerate(file, 1):
                if match(pattern, line, flags):
                    file_matches.append((l, line.rstrip('\n')))
                    if 'l' in flags:
                        break
            if file_matches:
                matches.append((file_name, file_matches))
    return formatter(matches, flags)

def match(pattern, line, flags):
    if 'i' in flags:
        pattern, line = pattern.lower(), line.lower()
    line = line.rstrip('\n')
    if 'x' in flags:
        return pattern == line.strip()
    if 'v' in flags:
        return pattern not in line
    return pattern in line

def formatter(matches, flags):
    output = []
    use_filename = len(matches) > 1 and 'l' not in flags
    for filename, lines in matches:
        for ln, line in lines:
            if 'l' in flags:
                output.append(f"{filename}\n")
                break
            if 'n' in flags:
                formatted_line = f"{ln}:{line}"
            else:
                formatted_line = line
            if use_filename:
                formatted_line = f"{filename}:{formatted_line}"
            output.append(formatted_line + '\n')
    return ''.join(output)