class Markdown {

    String parse(String markdown) {
        final StringBuilder result = new StringBuilder();
        boolean activeList = false;
        String[] lines = markdown.split("\n");

        for (String line : lines) {
            Line theLine = parseLine(line);

            if (theLine.lineType == LineType.LIST_ITEM && !activeList) {
                activeList = true;
                result.append("<ul>").append(theLine.value);
            } else if (theLine.lineType == LineType.LIST_ITEM && activeList) {
                result.append(theLine.value);
            } else if (theLine.lineType != LineType.LIST_ITEM && activeList) {
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

    private Line parseLine(String line) {
        if (line.startsWith("#")) {
            int count = 0;
            while (count < line.length() && line.charAt(count) == '#') {
                count++;
            }
            if (count > 0 && count < 7 && line.length() > count && line.charAt(count) == ' ') {
                return new Line("<h" + count + ">" + line.substring(count + 1) + "</h" + count + ">", LineType.HEADER);
            }
        } else if (line.startsWith("* ")) {
            return new Line("<li>" + parseSomeSymbols(line.substring(2)) + "</li>", LineType.LIST_ITEM);
        }

        return new Line("<p>" + parseSomeSymbols(line) + "</p>", LineType.PARAGRAPH);
    }


    private String parseSomeSymbols(String markdown) {
        String workingOn = markdown;
        int strongIndex = workingOn.indexOf("__");
        while (strongIndex != -1) {
            int strongEndIndex = workingOn.indexOf("__", strongIndex + 2);
            if (strongEndIndex != -1) {
                String content = workingOn.substring(strongIndex + 2, strongEndIndex);
                workingOn = workingOn.substring(0, strongIndex) + "<strong>" + content + "</strong>" + workingOn.substring(strongEndIndex + 2);
                strongIndex = workingOn.indexOf("__", strongIndex + "<strong></strong>".length());
            } else {
                break;
            }
            strongIndex = workingOn.indexOf("__");
        }

        int emIndex = workingOn.indexOf("_");
        while (emIndex != -1) {
            int emEndIndex = workingOn.indexOf("_", emIndex + 1);
            if (emEndIndex != -1) {
                String content = workingOn.substring(emIndex + 1, emEndIndex);
                workingOn = workingOn.substring(0, emIndex) + "<em>" + content + "</em>" + workingOn.substring(emEndIndex + 1);
                emIndex = workingOn.indexOf("_", emIndex + "<em></em>".length());

            } else {
                break;
            }
            emIndex = workingOn.indexOf("_");
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