import re


def parse(markdown):
    lines = markdown.splitlines()
    result = []
    in_list = False

    for i, line in enumerate(lines):
        line = parse_line(line)
        if line.startswith('<li>'):
            if not in_list:
                result.append('<ul>')
                in_list = True
            result.append(line)
        else:
            if in_list:
                result.append('</ul>')
                in_list = False
            result.append(line)

    if in_list:
        result.append('</ul>')

    return ''.join(result)


def parse_line(markdown):
    markdown = emphasis(markdown)

    header_match = re.match(r'#{1,6} (.+)', markdown)
    if header_match:
        level = markdown.index(' ')
        return f'<h{level}>{header_match.group(1)}</h{level}>'

    list_match = re.match(r'\* (.*)', markdown)
    if list_match:
        return f'<li>{list_match.group(1)}</li>'

    return f'<p>{markdown}</p>'


def emphasis(markdown):
    markdown = re.sub(r'__(.*?)__', r'<strong>\1</strong>', markdown)
    markdown = re.sub(r'_(.*?)_', r'<em>\1</em>', markdown)
    return markdown