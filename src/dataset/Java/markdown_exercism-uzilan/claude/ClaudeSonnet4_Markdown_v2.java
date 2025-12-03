class Markdown {

    String parse(String markdown) {
        final StringBuilder result = new StringBuilder();
        boolean activeList = false;
        
        final String[] lines = markdown.split("\n");
        
        for (final String line : lines) {
            Line theLine = parseHeader(line);
            
            if (theLine == Line.MISSING) {
                theLine = parseListItem(line);
            }
            
            if (theLine == Line.MISSING) {
                theLine = parseParagraph(line);
            }
            
            if (theLine.lineType == LineType.LIST_ITEM && !activeList) {
                activeList = true;
                result.append("<ul>").append(theLine.value);
            } else if (activeList && theLine.lineType != LineType.LIST_ITEM) {
                activeList = false;
                result.append("</ul>").append(theLine.value);
            } else {
                result.append(theLine.value);
            }
        }
        
        if (activeList) {
            result.append("</ul>");
        }
        
        return result.toString();
    }

    private Line parseHeader(String markdown) {
        int count = 0;
        final int length = markdown.length();
        
        while (count < length && markdown.charAt(count) == '#') {
            count++;
        }
        
        if (count == 0 || count >= length || markdown.charAt(count) != ' ') {
            return Line.MISSING;
        }
        
        final String content = markdown.substring(count + 1);
        final String tag = "<h" + count + ">";
        final String closeTag = "</h" + count + ">";
        
        return new Line(tag + content + closeTag, LineType.HEADER);
    }

    private Line parseListItem(String markdown) {
        if (markdown.length() < 2 || markdown.charAt(0) != '*' || markdown.charAt(1) != ' ') {
            return Line.MISSING;
        }
        
        final String content = parseSomeSymbols(markdown.substring(2));
        return new Line("<li>" + content + "</li>", LineType.LIST_ITEM);
    }

    private Line parseParagraph(String markdown) {
        return new Line("<p>" + parseSomeSymbols(markdown) + "</p>", LineType.PARAGRAPH);
    }

    private String parseSomeSymbols(String markdown) {
        String result = markdown;
        
        // Process strong emphasis first (__)
        int start = 0;
        while ((start = result.indexOf("__", start)) != -1) {
            int end = result.indexOf("__", start + 2);
            if (end != -1) {
                String content = result.substring(start + 2, end);
                result = result.substring(0, start) + "<strong>" + content + "</strong>" + result.substring(end + 2);
                start += 17; // length of "<strong></strong>"
            } else {
                break;
            }
        }
        
        // Process emphasis (_)
        start = 0;
        while ((start = result.indexOf("_", start)) != -1) {
            int end = result.indexOf("_", start + 1);
            if (end != -1) {
                String content = result.substring(start + 1, end);
                result = result.substring(0, start) + "<em>" + content + "</em>" + result.substring(end + 1);
                start += 9; // length of "<em></em>"
            } else {
                break;
            }
        }
        
        return result;
    }

    private static class Line {
        private final String value;
        private final LineType lineType;
        
        private static final Line MISSING = new Line("", LineType.MISSING);
        
        private Line(final String value, final LineType lineType) {
            this.value = value;
            this.lineType = lineType;
        }
    }

    private enum LineType {HEADER, LIST_ITEM, PARAGRAPH, MISSING}
}