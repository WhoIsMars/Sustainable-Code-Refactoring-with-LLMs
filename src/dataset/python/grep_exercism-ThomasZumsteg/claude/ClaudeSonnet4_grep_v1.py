def grep(pattern, files, flags=''):
    matches = []
    flag_i = 'i' in flags
    flag_l = 'l' in flags
    flag_x = 'x' in flags
    flag_v = 'v' in flags
    
    # Pre-process pattern for case-insensitive matching
    search_pattern = pattern.lower() if flag_i else pattern
    
    for file_name in files:
        file_matches = []
        with open(file_name, 'r') as f:
            for l, line in enumerate(f, 1):
                if match_optimized(search_pattern, line, flag_i, flag_x, flag_v):
                    file_matches.append((l, line))
                    if flag_l:
                        break
        matches.append((file_name, file_matches))
    return formatter(matches, flags)

def match(pattern, line, flags):
    flag_i = 'i' in flags
    flag_x = 'x' in flags
    flag_v = 'v' in flags
    
    search_pattern = pattern.lower() if flag_i else pattern
    return match_optimized(search_pattern, line, flag_i, flag_x, flag_v)

def match_optimized(pattern, line, flag_i, flag_x, flag_v):
    search_line = line.lower() if flag_i else line
    
    if flag_x:
        return pattern == search_line.strip()
    elif flag_v:
        return pattern not in search_line
    
    return pattern in search_line

def formatter(matches, flags):
    flag_l = 'l' in flags
    flag_n = 'n' in flags
    multiple_files = len(matches) > 1 and not flag_l
    
    output = []
    
    for filename, lines in matches:
        for ln, line in lines:
            if flag_l:
                output.append(f'{filename}\n')
                break
            elif multiple_files:
                if flag_n:
                    output.append(f'{filename}:{ln}:{line}')
                else:
                    output.append(f'{filename}:{line}')
            else:
                if flag_n:
                    output.append(f'{ln}:{line}')
                else:
                    output.append(line)
    
    return ''.join(output)