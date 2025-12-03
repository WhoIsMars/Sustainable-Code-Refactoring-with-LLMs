def grep(pattern, files, flags=''):
    matches = []
    list_only = 'l' in flags
    case_insensitive = 'i' in flags
    exact_match = 'x' in flags
    invert_match = 'v' in flags
    
    if case_insensitive:
        pattern = pattern.lower()
    
    for file_name in files:
        file_matches = []
        try:
            with open(file_name, 'r') as f:
                for l, line in enumerate(f, 1):
                    if _match_line(pattern, line, case_insensitive, exact_match, invert_match):
                        file_matches.append((l, line))
                        if list_only:
                            break
        except (IOError, OSError):
            continue
        matches.append((file_name, file_matches))
    return formatter(matches, flags)

def _match_line(pattern, line, case_insensitive, exact_match, invert_match):
    if case_insensitive:
        line = line.lower()
    
    if exact_match:
        return pattern == line.strip()
    elif invert_match:
        return pattern not in line
    
    return pattern in line

def match(pattern, line, flags):
    case_insensitive = 'i' in flags
    exact_match = 'x' in flags
    invert_match = 'v' in flags
    
    return _match_line(pattern, line, case_insensitive, exact_match, invert_match)

def formatter(matches, flags):
    list_only = 'l' in flags
    show_line_numbers = 'n' in flags
    multiple_files = len(matches) > 1 and not list_only
    
    if list_only:
        format_str = '{filename}\n'
    elif show_line_numbers:
        format_str = '{ln}:{line}'
    else:
        format_str = '{line}'
    
    if multiple_files:
        format_str = '{filename}:' + format_str
    
    output = []
    for filename, lines in matches:
        for ln, line in lines:
            output.append(format_str.format(ln=ln, line=line, filename=filename))
            if list_only:
                break
    
    return ''.join(output)