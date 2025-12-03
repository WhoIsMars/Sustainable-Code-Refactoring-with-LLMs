class Markdown {

    String parse(String markdown) {
        final StringBuilder result = new StringBuilder();
        boolean activeList = false;
        String[] lines = markdown.split("\n");

        for (int i = 0; i < lines.length; i++) {
            String line = lines[i];
            Line theLine = parseLine(line);

            if (theLine.lineType == LineType.LIST_ITEM) {
                if (!activeList) {
                    activeList = true;
                    result.append("<ul>");
                    result.append(theLine.value);
                } else {
                    result.append(theLine.value);
                }
                if (i == lines.length - 1 || parseLine(lines[i + 1]).lineType != LineType.LIST_ITEM) {
                    result.append("</ul>");
                    activeList = false;
                }
            } else {
                if (activeList) {
                    result.append("</ul>");
                    activeList = false;
                }
                result.append(theLine.value);
            }
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
                return new Line(
                        "<h" + count + ">" + parseSomeSymbols(line.substring(count + 1)) + "</h" + count + ">",
                        LineType.HEADER);
            }
        } else if (line.startsWith("* ")) {
            final String skipAsterisk = line.substring(2);
            final String listItemString = parseSomeSymbols(skipAsterisk);
            return new Line(
                    "<li>" + listItemString + "</li>",
                    LineType.LIST_ITEM);
        }

        return new Line(
                "<p>" + parseSomeSymbols(line) + "</p>",
                LineType.PARAGRAPH);
    }


    private String parseSomeSymbols(String markdown) {
        String workingOn = markdown;
        int strongIndex = workingOn.indexOf("__");
        while (strongIndex != -1) {
            int endIndex = workingOn.indexOf("__", strongIndex + 2);
            if (endIndex != -1) {
                String replacement = "<strong>" + workingOn.substring(strongIndex + 2, endIndex) + "</strong>";
                workingOn = workingOn.substring(0, strongIndex) + replacement + workingOn.substring(endIndex + 2);
                strongIndex = workingOn.indexOf("__", strongIndex + replacement.length());
            } else {
                break;
            }
            strongIndex = workingOn.indexOf("__");
        }

        int emIndex = workingOn.indexOf("_");
        while (emIndex != -1) {
            int endIndex = workingOn.indexOf("_", emIndex + 1);
            if (endIndex != -1) {
                String replacement = "<em>" + workingOn.substring(emIndex + 1, endIndex) + "</em>";
                workingOn = workingOn.substring(0, emIndex) + replacement + workingOn.substring(endIndex + 1);
                emIndex = workingOn.indexOf("_", emIndex + replacement.length());
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

        private static Line MISSING = new Line("", LineType.MISSING);

        private Line(final String value, final LineType lineType) {
            this.value = value;
            this.lineType = lineType;
        }
    }

    private enum LineType {HEADER, LIST_ITEM, PARAGRAPH, MISSING}
}