class Markdown {

    String parse(String markdown) {
        final StringBuilder result = new StringBuilder(markdown.length() * 2);
        boolean activeList = false;
        
        final String[] lines = markdown.split("\n");
        
        for (final String line : lines) {
            Line theLine = parseHeader(line);
            
            if (theLine.lineType == LineType.MISSING) {
                theLine = parseListItem(line);
            }
            
            if (theLine.lineType == LineType.MISSING) {
                theLine = parseParagraph(line);
            }
            
            if (theLine.lineType == LineType.LIST_ITEM) {
                if (!activeList) {
                    activeList = true;
                    result.append("<ul>");
                }
                result.append(theLine.value);
            } else {
                if (activeList) {
                    activeList = false;
                    result.append("</ul>");
                }
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
        
        final StringBuilder header = new StringBuilder(32);
        header.append("<h").append(count).append(">")
              .append(markdown.substring(count + 1))
              .append("</h").append(count).append(">");
        
        return new Line(header.toString(), LineType.HEADER);
    }

    private Line parseListItem(String markdown) {
        if (markdown.length() < 2 || !markdown.startsWith("* ")) {
            return Line.MISSING;
        }
        
        final String content = parseSomeSymbols(markdown.substring(2));
        final StringBuilder listItem = new StringBuilder(content.length() + 9);
        listItem.append("<li>").append(content).append("</li>");
        
        return new Line(listItem.toString(), LineType.LIST_ITEM);
    }

    private Line parseParagraph(String markdown) {
        final String content = parseSomeSymbols(markdown);
        final StringBuilder paragraph = new StringBuilder(content.length() + 7);
        paragraph.append("<p>").append(content).append("</p>");
        
        return new Line(paragraph.toString(), LineType.PARAGRAPH);
    }

    private String parseSomeSymbols(String markdown) {
        String result = markdown;
        
        int strongStart = result.indexOf("__");
        while (strongStart != -1) {
            int strongEnd = result.indexOf("__", strongStart + 2);
            if (strongEnd != -1) {
                final String before = result.substring(0, strongStart);
                final String content = result.substring(strongStart + 2, strongEnd);
                final String after = result.substring(strongEnd + 2);
                result = before + "<strong>" + content + "</strong>" + after;
                strongStart = result.indexOf("__", strongStart + 17);
            } else {
                break;
            }
        }
        
        int emStart = result.indexOf("_");
        while (emStart != -1) {
            if (emStart > 0 && result.charAt(emStart - 1) == '_') {
                emStart = result.indexOf("_", emStart + 1);
                continue;
            }
            if (emStart < result.length() - 1 && result.charAt(emStart + 1) == '_') {
                emStart = result.indexOf("_", emStart + 2);
                continue;
            }
            
            int emEnd = result.indexOf("_", emStart + 1);
            while (emEnd != -1 && emEnd < result.length() - 1 && result.charAt(emEnd + 1) == '_') {
                emEnd = result.indexOf("_", emEnd + 2);
            }
            
            if (emEnd != -1) {
                final String before = result.substring(0, emStart);
                final String content = result.substring(emStart + 1, emEnd);
                final String after = result.substring(emEnd + 1);
                result = before + "<em>" + content + "</em>" + after;
                emStart = result.indexOf("_", emStart + 9);
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