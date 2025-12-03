class Markdown {

    String parse(String markdown) {
        String[] lines = markdown.split("\n");
        StringBuilder result = new StringBuilder();
        boolean activeList = false;

        for (String line : lines) {
            String parsedLine = parseHeader(line);

            if (parsedLine == null) {
                parsedLine = parseListItem(line);
            }

            if (parsedLine == null) {
                parsedLine = parseParagraph(line);
            }

            if (parsedLine.startsWith("<li>") && !activeList) {
                activeList = true;
                result.append("<ul>");
            } else if (!parsedLine.startsWith("<li>") && activeList) {
                activeList = false;
                result.append("</ul>");
            }

            result.append(parsedLine);
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

        return "<h" + count + ">" + markdown.substring(count + 1).trim() + "</h" + count + ">";
    }

    private String parseListItem(String markdown) {
        if (markdown.startsWith("* ")) {
            return "<li>" + parseSomeSymbols(markdown.substring(2).trim()) + "</li>";
        }
        return null;
    }

    private String parseParagraph(String markdown) {
        return "<p>" + parseSomeSymbols(markdown.trim()) + "</p>";
    }

    private String parseSomeSymbols(String markdown) {
        return markdown.replaceAll("__(.+?)__", "<strong>$1</strong>")
                       .replaceAll("_(.+?)_", "<em>$1</em>");
    }
}