class Markdown {

    String parse(String markdown) {
        final StringBuilder result = new StringBuilder();
        boolean activeList = false;
        String[] lines = markdown.split("\n");

        for (String line : lines) {
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
                    result.append("<ul>").append(theLine.value);
                } else {
                    result.append(theLine.value);
                }
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
        int length = markdown.length();
        while (count < length && markdown.charAt(count) == '#') {
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
        int strongIndex = workingOn.indexOf("__");
        while (strongIndex != -1) {
            int strongEndIndex = workingOn.indexOf("__", strongIndex + 2);
            if (strongEndIndex != -1) {
                String content = workingOn.substring(strongIndex + 2, strongEndIndex);
                workingOn = workingOn.substring(0, strongIndex) + "<strong>" + content + "</strong>" + workingOn.substring(strongEndIndex + 2);
                strongIndex = workingOn.indexOf("__", strongEndIndex + 15); //15 is length of <strong>...</strong>
            } else {
                break;
            }
            strongIndex = workingOn.indexOf("__", strongIndex + 1);
        }

        int emIndex = workingOn.indexOf("_");
        while (emIndex != -1) {
            int emEndIndex = workingOn.indexOf("_", emIndex + 1);
            if (emEndIndex != -1) {
                String content = workingOn.substring(emIndex + 1, emEndIndex);
                workingOn = workingOn.substring(0, emIndex) + "<em>" + content + "</em>" + workingOn.substring(emEndIndex + 1);
                emIndex = workingOn.indexOf("_", emEndIndex + 9); //9 is length of <em>...</em>
            } else {
                break;
            }
            emIndex = workingOn.indexOf("_", emIndex + 1);
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