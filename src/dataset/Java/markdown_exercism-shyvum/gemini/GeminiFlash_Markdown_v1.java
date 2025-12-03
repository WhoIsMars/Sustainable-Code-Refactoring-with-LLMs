class Markdown {

    String parse(String markdown) {
        StringBuilder result = new StringBuilder();
        String[] lines = markdown.split("\n");
        boolean activeList = false;

        for (String line : lines) {
            String theLine = null;

            if (line.startsWith("#")) {
                theLine = parseHeader(line);
            } else if (line.startsWith("*")) {
                theLine = parseListItem(line);
            } else {
                theLine = parseParagraph(line);
            }

            if (theLine != null && theLine.startsWith("<li>") && !theLine.startsWith("<h") && !theLine.startsWith("<p") && !activeList) {
                activeList = true;
                result.append("<ul>");
                result.append(theLine);
            } else if (theLine != null && !theLine.startsWith("<li>") && activeList) {
                activeList = false;
                result.append("</ul>");
                result.append(theLine);
            } else {
                if (theLine != null) {
                    result.append(theLine);
                }
            }
        }

        if (activeList) {
            result.append("</ul>");
        }

        return result.toString();
    }

    private String parseHeader(String markdown) {
        int count = 0;
        while (count < markdown.length() && markdown.charAt(count) == '#') {
            count++;
        }

        if (count == 0) {
            return null;
        }

        return "<h" + count + ">" + markdown.substring(count).trim() + "</h" + count + ">";
    }

    private String parseListItem(String markdown) {
        String skipAsterisk = markdown.substring(1).trim();
        String listItemString = parseSomeSymbols(skipAsterisk);
        return "<li>" + listItemString + "</li>";
    }

    private String parseParagraph(String markdown) {
        return "<p>" + parseSomeSymbols(markdown) + "</p>";
    }

    private String parseSomeSymbols(String markdown) {
        String workingOn = markdown.replaceFirst("__(.+?)__", "<strong>$1</strong>");
        return workingOn.replaceFirst("_(.+?)_", "<em>$1</em>");
    }
}