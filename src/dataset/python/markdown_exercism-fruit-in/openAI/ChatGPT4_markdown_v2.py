import re


def parse(markdown):
    lines = []
    in_list = False

    for line in markdown.splitlines():
        parsed_line = parse_line(line)
        if not in_list and parsed_line.startswith('<li>'):
            lines.append('<ul>')
            in_list = True
        if in_list and not parsed_line.startswith('<li>'):
            lines.append('</ul>')
            in_list = False
        lines.append(parsed_line)

    if in_list:
        lines.append('</ul>')

    return ''.join(lines)


def parse_line(markdown):
    markdown = emphasis(markdown)

    if markdown.startswith('#'):
        header_level = len(markdown) - len(markdown.lstrip('#'))
        return f'<h{header_level}>{markdown[header_level + 1:].strip()}</h{header_level}>'
    elif markdown.startswith('* '):
        return f'<li>{markdown[2:].strip()}</li>'
    else:
        return f'<p>{markdown.strip()}</p>'


def emphasis(markdown):
    markdown = re.sub(r'__(.*?)__', r'<strong>\1</strong>', markdown)
    markdown = re.sub(r'_(.*?)_', r'<em>\1</em>', markdown)
    return markdown