def grep(pattern, files, flags=''):
    matches = []
    include_line_number = 'n' in flags
    only_file_names = 'l' in flags
    invert_match = 'v' in flags
    ignore_case = 'i' in flags
    exact_match = 'x' in flags
    multiple_files = len(files) > 1 and not only_file_names

    for file_name in files:
        file_matches = []
        try:
            with open(file_name, 'r') as f:
                for l, line in enumerate(f, 1):
                    if ignore_case:
                        pattern_lower = pattern.lower()
                        line_lower = line.lower()
                    else:
                        pattern_lower = pattern
                        line_lower = line

                    if exact_match:
                        matched = pattern_lower == line_lower.strip()
                    elif invert_match:
                        matched = pattern_lower not in line_lower
                    else:
                        matched = pattern_lower in line_lower

                    if matched:
                        file_matches.append((l, line))
                        if only_file_names:
                            break
        except FileNotFoundError:
            continue  # Or handle the exception as needed

        matches.append((file_name, file_matches))

    output = []
    for filename, lines in matches:
        for ln, line in lines:
            if only_file_names:
                output.append(f'{filename}\n')
                break
            elif include_line_number and multiple_files:
                output.append(f'{filename}:{ln}:{line}')
            elif include_line_number:
                output.append(f'{ln}:{line}')
            elif multiple_files:
                output.append(f'{filename}:{line}')
            else:
                output.append(line)

    return ''.join(output)