def grep(pattern, files, flags=''):
    matches = []
    for file_name in files:
        with open(file_name) as f:
            file_matches = []
            for l, line in enumerate(f, 1):
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

    if 'x' in flags:
        return pattern == line.strip()
    if 'v' in flags:
        return pattern not in line

    return pattern in line

def formatter(matches, flags):
    output = []
    use_line_numbers = 'n' in flags
    show_filenames = len(matches) > 1 and 'l' not in flags
    list_only_filenames = 'l' in flags

    for filename, lines in matches:
        if list_only_filenames:
            output.append(f"{filename}\n")
            continue
        for ln, line in lines:
            formatted_line = f"{filename}:" if show_filenames else ""
            if use_line_numbers:
                formatted_line += f"{ln}:"
            formatted_line += line
            output.append(formatted_line + '\n')
            if list_only_filenames:
                break

    return ''.join(output)