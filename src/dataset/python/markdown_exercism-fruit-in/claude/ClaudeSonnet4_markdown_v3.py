import re

# Pre-compile regex patterns for better performance
_HEADER_PATTERN = re.compile(r'^(#{1,6}) (.+)$')
_UNORDERED_LIST_PATTERN = re.compile(r'^\* (.*)$')
_LI_PATTERN = re.compile(r'^<li>')
_STRONG_PATTERN = re.compile(r'__([^_]+)__')
_EM_PATTERN = re.compile(r'_([^_]+)_')


def parse(markdown):
    if not markdown:
        return ''
    
    lines = markdown.splitlines()
    result = []
    in_list = False
    
    for i, line in enumerate(lines):
        parsed_line = parse_line(line)
        
        is_li = parsed_line.startswith('<li>')
        next_is_li = (i + 1 < len(lines) and 
                     parse_line(lines[i + 1]).startswith('<li>')) if i + 1 < len(lines) else False
        
        if not in_list and is_li:
            parsed_line = '<ul>' + parsed_line
            in_list = True
        elif in_list and not next_is_li:
            parsed_line += '</ul>'
            in_list = False
            
        result.append(parsed_line)
    
    return ''.join(result)


def parse_line(markdown):
    markdown = emphasis(markdown)
    
    header_match = _HEADER_PATTERN.match(markdown)
    if header_match:
        level = len(header_match.group(1))
        content = header_match.group(2)
        return f'<h{level}>{content}</h{level}>'
    
    list_match = _UNORDERED_LIST_PATTERN.match(markdown)
    if list_match:
        return f'<li>{list_match.group(1)}</li>'
    
    return f'<p>{markdown}</p>'


def emphasis(markdown):
    markdown = _STRONG_PATTERN.sub(r'<strong>\1</strong>', markdown)
    markdown = _EM_PATTERN.sub(r'<em>\1</em>', markdown)
    return markdown


def is_header(markdown):
    return _HEADER_PATTERN.match(markdown) is not None


def is_unordered_list(markdown):
    return _UNORDERED_LIST_PATTERN.match(markdown) is not None