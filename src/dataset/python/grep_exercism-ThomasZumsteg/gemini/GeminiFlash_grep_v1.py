import re

def grep(pattern, files, flags=''):
    matches = []
    ignore_case = 'i' in flags
    whole_line = 'x' in flags
    invert_match = 'v' in flags
    only_filenames = 'l' in flags
    number_lines = 'n' in flags
    multiple_files = len(files) > 1 and not only_filenames

    if ignore_case:
        pattern = pattern.lower()

    for file_name in files:
        file_matches = []
        try:
            with open(file_name, 'r') as f:
                for l, line in enumerate(f, 1):
                    processed_line = line.rstrip()
                    if ignore_case:
                        processed_line = processed_line.lower()

                    if whole_line:
                        matched = pattern == processed_line
                    elif invert_match:
                        matched = pattern not in processed_line
                    else:
                        matched = pattern in processed_line

                    if matched:
                        file_matches.append((l, line))
                        if only_filenames:
                            break
        except FileNotFoundError:
            continue  # Or handle the error as needed

        matches.append((file_name, file_matches))

    output = []
    for filename, lines in matches:
        for ln, line in lines:
            if only_filenames:
                output.append(f'{filename}\n')
                break
            else:
                prefix = f'{filename}:' if multiple_files else ''
                if number_lines:
                    output.append(f'{prefix}{ln}:{line}')
                else:
                    output.append(f'{prefix}{line}')

    return ''.join(output)