def grep(pattern, files, flags=''):
    matches = []
    flags_set = set(flags)
    case_insensitive = 'i' in flags_set
    exact_match = 'x' in flags_set
    invert_match = 'v' in flags_set
    files_only = 'l' in flags_set
    
    if case_insensitive:
        pattern = pattern.lower()
    
    for file_name in files:
        file_matches = []
        try:
            with open(file_name, 'r') as f:
                for l, line in enumerate(f, 1):
                    if match_optimized(pattern, line, case_insensitive, exact_match, invert_match):
                        file_matches.append((l, line))
                        if files_only:
                            break
        except (IOError, OSError):
            continue
        matches.append((file_name, file_matches))
    return formatter(matches, flags_set)

def match(pattern, line, flags):
    flags_set = set(flags)
    case_insensitive = 'i' in flags_set
    exact_match = 'x' in flags_set
    invert_match = 'v' in flags_set
    
    if case_insensitive:
        pattern, line = pattern.lower(), line.lower()
    
    return match_optimized(pattern, line, False, exact_match, invert_match)

def match_optimized(pattern, line, case_insensitive, exact_match, invert_match):
    if case_insensitive:
        line = line.lower()
    
    if exact_match:
        return pattern == line.rstrip('\n\r')
    elif invert_match:
        return pattern not in line
    
    return pattern in line

def formatter(matches, flags):
    if isinstance(flags, str):
        flags = set(flags)
    
    output = []
    files_only = 'l' in flags
    show_line_numbers = 'n' in flags
    multiple_files = len(matches) > 1 and not files_only
    
    for filename, lines in matches:
        if files_only and lines:
            output.append(f'{filename}\n')
            continue
            
        for ln, line in lines:
            line = line.rstrip('\n\r')
            if multiple_files:
                if show_line_numbers:
                    output.append(f'{filename}:{ln}:{line}\n')
                else:
                    output.append(f'{filename}:{line}\n')
            else:
                if show_line_numbers:
                    output.append(f'{ln}:{line}\n')
                else:
                    output.append(f'{line}\n')
    
    return ''.join(output)