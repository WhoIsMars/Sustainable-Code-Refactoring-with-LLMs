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
        return new Line(
                "<h" + count + ">" + content + "</h" + count + ">",
                LineType.HEADER);
    }

    private Line parseListItem(String markdown) {
        if (markdown.length() < 2 || markdown.charAt(0) != '*' || markdown.charAt(1) != ' ') {
            return Line.MISSING;
        }
        
        final String content = parseSomeSymbols(markdown.substring(2));
        return new Line(
                "<li>" + content + "</li>",
                LineType.LIST_ITEM);
    }

    private Line parseParagraph(String markdown) {
        return new Line(
                "<p>" + parseSomeSymbols(markdown) + "</p>",
                LineType.PARAGRAPH);
    }

    private String parseSomeSymbols(String markdown) {
        String result = markdown;
        
        int strongStart = result.indexOf("__");
        while (strongStart != -1) {
            int strongEnd = result.indexOf("__", strongStart + 2);
            if (strongEnd != -1) {
                String content = result.substring(strongStart + 2, strongEnd);
                result = result.substring(0, strongStart) + "<strong>" + content + "</strong>" + result.substring(strongEnd + 2);
                strongStart = result.indexOf("__", strongStart + 17);
            } else {
                break;
            }
        }
        
        int emStart = result.indexOf("_");
        while (emStart != -1) {
            int emEnd = result.indexOf("_", emStart + 1);
            if (emEnd != -1) {
                String content = result.substring(emStart + 1, emEnd);
                result = result.substring(0, emStart) + "<em>" + content + "</em>" + result.substring(emEnd + 1);
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