class Markdown {

    String parse(String markdown) {
        StringBuilder result = new StringBuilder();
        String[] lines = markdown.split("\n");
        boolean activeList = false;

        for (String line : lines) {
            String theLine = parseLine(line);

            if (theLine.startsWith("<li>") && !theLine.startsWith("<h") && !theLine.startsWith("<p>") && !activeList) {
                activeList = true;
                result.append("<ul>");
                result.append(theLine);
            } else if (!theLine.startsWith("<li>") && activeList) {
                activeList = false;
                result.append("</ul>");
                result.append(theLine);
            } else {
                result.append(theLine);
            }
        }

        if (activeList) {
            result.append("</ul>");
        }

        return result.toString();
    }

    private String parseLine(String line) {
        String theLine = parseHeader(line);
        if (theLine != null) return theLine;

        theLine = parseListItem(line);
        if (theLine != null) return theLine;

        return parseParagraph(line);
    }

    private String parseHeader(String markdown) {
        int count = 0;
        int len = markdown.length();

        while (count < len && markdown.charAt(count) == '#') {
            count++;
        }

        if (count == 0) {
            return null;
        }

        return "<h" + count + ">" + markdown.substring(count).trim() + "</h" + count + ">";
    }

    private String parseListItem(String markdown) {
        if (markdown.startsWith("* ")) {
            String skipAsterisk = markdown.substring(2);
            String listItemString = parseSomeSymbols(skipAsterisk);
            return "<li>" + listItemString + "</li>";
        }

        return null;
    }

    private String parseParagraph(String markdown) {
        return "<p>" + parseSomeSymbols(markdown) + "</p>";
    }

    private String parseSomeSymbols(String markdown) {
        String workingOn = markdown.replaceAll("__(.+?)__", "<strong>$1</strong>");
        return workingOn.replaceAll("_(.+?)_", "<em>$1</em>");
    }
}