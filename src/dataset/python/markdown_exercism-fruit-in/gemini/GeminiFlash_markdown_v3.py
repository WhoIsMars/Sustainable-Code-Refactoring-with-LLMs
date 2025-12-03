import re


def parse(markdown):
    lines = markdown.splitlines()
    result = []
    in_list = False

    for i, line in enumerate(lines):
        line = parse_line(line)
        if re.match(r'<li>', line):
            if not in_list:
                result.append('<ul>')
                in_list = True
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

    header_match = is_header(markdown)
    if header_match:
        level = header_match.end() - header_match.start() - 1
        return f'<h{level}>{markdown[level + 1:]}</h{level}>'

    list_match = is_unordered_list(markdown)
    if list_match:
        return f'<li>{markdown[2:]}</li>'

    return f'<p>{markdown}</p>'


def emphasis(markdown):
    markdown = re.sub(r'__(.*?)__', r'<strong>\1</strong>', markdown)
    markdown = re.sub(r'_(.*?)_', r'<em>\1</em>', markdown)
    return markdown


def is_header(markdown):
    return re.match(r'#{1,6} (.+)', markdown)


def is_unordered_list(markdown):
    return re.match(r'\* (.*)', markdown)