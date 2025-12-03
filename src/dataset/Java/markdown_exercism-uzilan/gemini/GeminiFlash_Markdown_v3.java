class Markdown {

    String parse(String markdown) {
        final StringBuilder result = new StringBuilder();
        boolean activeList = false;
        String[] lines = markdown.split("\n");

        for (String line : lines) {
            Line theLine = parseLine(line);

            if (theLine.lineType == LineType.LIST_ITEM && !activeList) {
                activeList = true;
                result.append("<ul>");
                result.append(theLine.value);
            } else if (theLine.lineType == LineType.LIST_ITEM && activeList) {
                result.append(theLine.value);
            } else if (theLine.lineType != LineType.LIST_ITEM && activeList) {
                activeList = false;
                result.append("</ul>");
                result.append(theLine.value);
            } else {
                result.append(theLine.value);
            }
        }

        if (activeList) {
            result.append("</ul>");
        }

        return result.toString();
    }

    private Line parseLine(String line) {
        if (line.startsWith("#")) {
            return parseHeader(line);
        } else if (line.startsWith("*")) {
            return parseListItem(line);
        } else {
            return parseParagraph(line);
        }
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
                "<h" + count + ">" + markdown.substring(count).trim() + "</h" + count + ">",
                LineType.HEADER);
    }

    private Line parseListItem(String markdown) {
        if (markdown.length() < 2 || markdown.charAt(0) != '*' || markdown.charAt(1) != ' ') {
            return Line.MISSING;
        }

        final String skipAsterisk = markdown.substring(2);
        final String listItemString = parseSomeSymbols(skipAsterisk);
        return new Line(
                "<li>" + listItemString + "</li>",
                LineType.LIST_ITEM);

    }

    private Line parseParagraph(String markdown) {
        return new Line(
                "<p>" + parseSomeSymbols(markdown) + "</p>",
                LineType.PARAGRAPH);
    }

    private String parseSomeSymbols(String markdown) {
        String workingOn = markdown;
        int strongStart = workingOn.indexOf("__");
        while (strongStart != -1) {
            int strongEnd = workingOn.indexOf("__", strongStart + 2);
            if (strongEnd != -1) {
                String content = workingOn.substring(strongStart + 2, strongEnd);
                workingOn = workingOn.substring(0, strongStart) + "<strong>" + content + "</strong>" + workingOn.substring(strongEnd + 2);
                strongStart = workingOn.indexOf("__", strongEnd + 1);
            } else {
                break;
            }
        }

        int emStart = workingOn.indexOf("_");
        while (emStart != -1) {
            int emEnd = workingOn.indexOf("_", emStart + 1);
            if (emEnd != -1) {
                String content = workingOn.substring(emStart + 1, emEnd);
                workingOn = workingOn.substring(0, emStart) + "<em>" + content + "</em>" + workingOn.substring(emEnd + 1);
                emStart = workingOn.indexOf("_", emEnd + 1);
            } else {
                break;
            }
        }
        return workingOn;
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