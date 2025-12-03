def grep(pattern, files, flags=''):
    matches = []
    flag_set = set(flags)
    is_list_only = 'l' in flag_set
    
    for file_name in files:
        file_matches = []
        try:
            with open(file_name, 'r') as f:
                for l, line in enumerate(f, 1):
                    if match(pattern, line, flag_set):
                        file_matches.append((l, line))
                        if is_list_only:
                            break
        except IOError:
            continue
        matches.append((file_name, file_matches))
    return formatter(matches, flag_set)

def match(pattern, line, flag_set):
    if 'i' in flag_set:
        pattern, line = pattern.lower(), line.lower()

    if 'x' in flag_set:
        return pattern == line.strip()
    elif 'v' in flag_set:
        return pattern not in line

    return pattern in line

def formatter(matches, flag_set):
    if 'l' in flag_set:
        return ''.join(f'{filename}\n' for filename, lines in matches if lines)
    
    output = []
    has_line_numbers = 'n' in flag_set
    multiple_files = len(matches) > 1
    
    for filename, lines in matches:
        for ln, line in lines:
            if multiple_files:
                if has_line_numbers:
                    output.append(f'{filename}:{ln}:{line}')
                else:
                    output.append(f'{filename}:{line}')
            else:
                if has_line_numbers:
                    output.append(f'{ln}:{line}')
                else:
                    output.append(line)

    return ''.join(output)