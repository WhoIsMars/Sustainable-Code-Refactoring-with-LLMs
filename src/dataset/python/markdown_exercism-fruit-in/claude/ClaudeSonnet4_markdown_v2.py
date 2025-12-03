import re

# Pre-compile regex patterns for better performance
HEADER_PATTERN = re.compile(r'^(#{1,6}) (.+)$')
LIST_PATTERN = re.compile(r'^\* (.*)$')
LI_PATTERN = re.compile(r'^<li>')
STRONG_PATTERN = re.compile(r'__(.+?)__')
EM_PATTERN = re.compile(r'_(.+?)_')


def parse(markdown):
    lines = markdown.splitlines()
    result = []
    start_list = False
    
    for i, line in enumerate(lines):
        parsed_line = parse_line(line)
        
        if not start_list and parsed_line.startswith('<li>'):
            parsed_line = '<ul>' + parsed_line
            start_list = True
        elif start_list and (i == len(lines) - 1 or not is_list_item(lines[i + 1])):
            parsed_line += '</ul>'
            start_list = False
            
        result.append(parsed_line)
    
    return ''.join(result)


def parse_line(markdown):
    markdown = emphasis(markdown)
    
    header_match = HEADER_PATTERN.match(markdown)
    if header_match:
        level = len(header_match.group(1))
        content = header_match.group(2)
        return f'<h{level}>{content}</h{level}>'
    
    list_match = LIST_PATTERN.match(markdown)
    if list_match:
        return f'<li>{list_match.group(1)}</li>'
    
    return f'<p>{markdown}</p>'


def emphasis(markdown):
    # Process strong emphasis first (__)
    markdown = STRONG_PATTERN.sub(r'<strong>\1</strong>', markdown)
    # Process emphasis (_)
    markdown = EM_PATTERN.sub(r'<em>\1</em>', markdown)
    return markdown


def is_list_item(line):
    return LIST_PATTERN.match(line) is not None


def is_header(markdown):
    return HEADER_PATTERN.match(markdown) is not None


def is_unordered_list(markdown):
    return LIST_PATTERN.match(markdown) is not None