import re

# Pre-compile regex patterns for better performance
_HEADER_PATTERN = re.compile(r'#{1,6} (.+)')
_UNORDERED_LIST_PATTERN = re.compile(r'\* (.*)')
_LI_PATTERN = re.compile(r'<li>')
_STRONG_PATTERN = re.compile(r'(.*)__(.*)__(.*)')
_EM_PATTERN = re.compile(r'(.*)_(.*)_(.*)')


def parse(markdown):
    if not markdown:
        return ''
    
    lines = markdown.splitlines()
    if not lines:
        return ''
    
    result = []
    start_list = False
    
    for i, line in enumerate(lines):
        parsed_line = parse_line(line)
        
        if not start_list and parsed_line.startswith('<li>'):
            parsed_line = '<ul>' + parsed_line
            start_list = True
        elif start_list and (i == len(lines) - 1 or not parse_line(lines[i + 1]).startswith('<li>')):
            parsed_line += '</ul>'
            start_list = False
            
        result.append(parsed_line)
    
    return ''.join(result)


def parse_line(markdown):
    markdown = emphasis(markdown)

    if is_header(markdown):
        i = markdown.index(' ')
        return '<h{0}>{1}</h{0}>'.format(i, markdown[i + 1:])
    elif is_unordered_list(markdown):
        return '<li>{}</li>'.format(markdown[2:])
    else:
        return '<p>{}</p>'.format(markdown)


def emphasis(markdown):
    # Process strong emphasis first
    match = _STRONG_PATTERN.match(markdown)
    while match:
        i = markdown.index('__')
        j = markdown.rindex('__')
        markdown = '{}<strong>{}</strong>{}'.format(
            markdown[:i], markdown[i + 2:j], markdown[j + 2:])
        match = _STRONG_PATTERN.match(markdown)

    # Process emphasis
    match = _EM_PATTERN.match(markdown)
    while match:
        i = markdown.index('_')
        j = markdown.rindex('_')
        markdown = '{}<em>{}</em>{}'.format(
            markdown[:i], markdown[i + 1:j], markdown[j + 1:])
        match = _EM_PATTERN.match(markdown)

    return markdown


def is_header(markdown):
    return _HEADER_PATTERN.match(markdown)


def is_unordered_list(markdown):
    return _UNORDERED_LIST_PATTERN.match(markdown)