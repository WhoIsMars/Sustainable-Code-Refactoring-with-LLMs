import re


def parse(markdown):
    lines = []
    start_list = False

    for line in markdown.splitlines():
        parsed_line = parse_line(line)
        if not start_list and parsed_line.startswith('<li>'):
            lines.append('<ul>' + parsed_line)
            start_list = True
        elif start_list and not parsed_line.startswith('<li>'):
            lines[-1] += '</ul>'
            lines.append(parsed_line)
            start_list = False
        else:
            lines.append(parsed_line)

    if start_list:
        lines[-1] += '</ul>'

    return ''.join(lines)


def parse_line(markdown):
    markdown = emphasis(markdown)

    if markdown.startswith('#'):
        i = markdown.find(' ')
        return f'<h{i}>{markdown[i + 1:]}</h{i}>'
    elif markdown.startswith('* '):
        return f'<li>{markdown[2:]}</li>'
    else:
        return f'<p>{markdown}</p>'


def emphasis(markdown):
    markdown = re.sub(r'__(.*?)__', r'<strong>\1</strong>', markdown)
    markdown = re.sub(r'_(.*?)_', r'<em>\1</em>', markdown)
    return markdown


def is_header(markdown):
    return markdown.startswith('#') and ' ' in markdown


def is_unordered_list(markdown):
    return markdown.startswith('* ')