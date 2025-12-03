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
    l_flag = 'l' in flags
    n_flag = 'n' in flags
    multi_file = len(matches) > 1 and not l_flag

    for filename, lines in matches:
        for ln, line in lines:
            if l_flag:
                output.append(f"{filename}\n")
                break
            prefix = f"{filename}:" if multi_file else ""
            if n_flag:
                output.append(f"{prefix}{ln}:{line}\n")
            else:
                output.append(f"{prefix}{line}\n")

    return ''.join(output)