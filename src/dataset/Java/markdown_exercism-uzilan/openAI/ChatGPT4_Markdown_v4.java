import java.util.regex.Pattern;

class Markdown {

    private static final Pattern STRONG_PATTERN = Pattern.compile("__(.+)__");
    private static final Pattern EM_PATTERN = Pattern.compile("_(.+)_");

    String parse(String markdown) {
        StringBuilder result = new StringBuilder();
        boolean activeList = false;

        for (String line : markdown.split("\n")) {
            Line theLine = parseHeader(line);

            if (theLine == Line.MISSING) {
                theLine = parseListItem(line);
            }

            if (theLine == Line.MISSING) {
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
        while (count < markdown.length() && markdown.charAt(count) == '#') {
            count++;
        }

        if (count == 0) {
            return Line.MISSING;
        }

        return new Line(
                "<h" + count + ">" + markdown.substring(count + 1).trim() + "</h" + count + ">",
                LineType.HEADER);
    }

    private Line parseListItem(String markdown) {
        if (!markdown.startsWith("* ")) {
            return Line.MISSING;
        }

        String listItemString = parseSomeSymbols(markdown.substring(2).trim());
        return new Line("<li>" + listItemString + "</li>", LineType.LIST_ITEM);
    }

    private Line parseParagraph(String markdown) {
        return new Line("<p>" + parseSomeSymbols(markdown.trim()) + "</p>", LineType.PARAGRAPH);
    }

    private String parseSomeSymbols(String markdown) {
        String workingOn = STRONG_PATTERN.matcher(markdown).replaceAll("<strong>$1</strong>");
        return EM_PATTERN.matcher(workingOn).replaceAll("<em>$1</em>");
    }

    private static class Line {
        private final String value;
        private final LineType lineType;

        private static final Line MISSING = new Line("", LineType.MISSING);

        private Line(String value, LineType lineType) {
            this.value = value;
            this.lineType = lineType;
        }
    }

    private enum LineType {HEADER, LIST_ITEM, PARAGRAPH, MISSING}
}