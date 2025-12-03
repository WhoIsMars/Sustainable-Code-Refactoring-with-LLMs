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

    if markdown.startswith('#'):
        match = re.match(r'^(#+) (.*)', markdown)
        if match:
            level = len(match.group(1))
            text = match.group(2)
            return f'<h{level}>{text}</h{level}>'
        else:
            return '<p>{}</p>'.format(markdown)
    elif markdown.startswith('* '):
        return '<li>{}</li>'.format(markdown[2:])
    else:
        return '<p>{}</p>'.format(markdown)


def emphasis(markdown):
    markdown = re.sub(r'__(.*?)__', r'<strong>\1</strong>', markdown)
    markdown = re.sub(r'_(.*?)_', r'<em>\1</em>', markdown)
    return markdown


def is_header(markdown):
    return markdown.startswith('#') and ' ' in markdown[:7]


def is_unordered_list(markdown):
    return markdown.startswith('* ')