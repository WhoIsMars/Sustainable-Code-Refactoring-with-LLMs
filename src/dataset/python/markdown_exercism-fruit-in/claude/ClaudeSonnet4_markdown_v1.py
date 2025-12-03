import re

# Pre-compile regex patterns for better performance
_HEADER_PATTERN = re.compile(r'^(#{1,6}) (.+)$')
_LIST_PATTERN = re.compile(r'^\* (.*)$')
_LI_PATTERN = re.compile(r'^<li>')
_STRONG_PATTERN = re.compile(r'__(.+?)__')
_EM_PATTERN = re.compile(r'_(.+?)_')


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
        
        if not start_list and _LI_PATTERN.match(parsed_line):
            parsed_line = '<ul>' + parsed_line
            start_list = True
        elif start_list and (i == len(lines) - 1 or not _LI_PATTERN.match(parse_line(lines[i + 1]))):
            parsed_line += '</ul>'
            start_list = False
            
        result.append(parsed_line)
    
    return ''.join(result)


def parse_line(markdown):
    markdown = emphasis(markdown)
    
    header_match = _HEADER_PATTERN.match(markdown)
    if header_match:
        level = len(header_match.group(1))
        content = header_match.group(2)
        return f'<h{level}>{content}</h{level}>'
    
    list_match = _LIST_PATTERN.match(markdown)
    if list_match:
        return f'<li>{list_match.group(1)}</li>'
    
    return f'<p>{markdown}</p>'


def emphasis(markdown):
    # Process strong emphasis first (__ patterns)
    markdown = _STRONG_PATTERN.sub(r'<strong>\1</strong>', markdown)
    
    # Process regular emphasis (_ patterns)
    markdown = _EM_PATTERN.sub(r'<em>\1</em>', markdown)
    
    return markdown


def is_header(markdown):
    return _HEADER_PATTERN.match(markdown) is not None


def is_unordered_list(markdown):
    return _LIST_PATTERN.match(markdown) is not None