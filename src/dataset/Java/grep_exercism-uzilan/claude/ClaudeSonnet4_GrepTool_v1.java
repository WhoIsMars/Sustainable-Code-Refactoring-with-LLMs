import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Stream;

import static java.util.stream.Collectors.joining;

public class GrepTool {

    public String grep(String text, List<String> flagList, List<String> fileNames) {
        final Flags flags = new Flags(fileNames.size() > 1, flagList);

        return fileNames.stream()
                .flatMap(file -> findInFile(text, file, flags))
                .collect(joining("\n"));
    }

    private Stream<String> findInFile(String text, String fileName, Flags flags) {
        try {
            final Path path = Paths.get(fileName);
            return Files.lines(path)
                    .map(line -> new LineWithNumber(line, 1))
                    .map(lineWithNumber -> {
                        lineWithNumber.lineNumber = lineWithNumber.lineNumber;
                        return lineWithNumber;
                    })
                    .filter(lineWithNumber -> matchLine(text, lineWithNumber.line, flags))
                    .map(lineWithNumber -> getLine(fileName, lineWithNumber.line, lineWithNumber.lineNumber, flags))
                    .distinct();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return Stream.empty();
    }

    private boolean matchLine(String text, String line, Flags flags) {
        return flags.invert != lineContainsText(text, line, flags);
    }

    private boolean lineContainsText(String text, String line, Flags flags) {
        if (flags.matchEntireLines) {
            return flags.caseInsensitiv ? line.equalsIgnoreCase(text) : line.equals(text);
        } else {
            return flags.caseInsensitiv ? line.toLowerCase().contains(text.toLowerCase()) : line.contains(text);
        }
    }

    private String getLine(String fileName, String line, int lineNumber, Flags flags) {
        if (flags.containsOneMatchingLine) {
            return fileName;
        }

        if (!flags.addFileName && !flags.addRowNumber) {
            return line;
        }

        StringBuilder sb = new StringBuilder();
        if (flags.addFileName) {
            sb.append(fileName).append(":");
        }
        if (flags.addRowNumber) {
            sb.append(lineNumber).append(":");
        }
        sb.append(line);

        return sb.toString();
    }

    private static class LineWithNumber {
        final String line;
        int lineNumber;

        LineWithNumber(String line, int lineNumber) {
            this.line = line;
            this.lineNumber = lineNumber;
        }
    }

    class Flags {

        final boolean addFileName;
        final boolean addRowNumber;
        final boolean containsOneMatchingLine;
        final boolean caseInsensitiv;
        final boolean invert;
        final boolean matchEntireLines;

        private Flags(boolean addFileName, List<String> flagList) {
            this.addFileName = addFileName;
            this.addRowNumber = flagList.contains("-n");
            this.containsOneMatchingLine = flagList.contains("-l");
            this.caseInsensitiv = flagList.contains("-i");
            this.invert = flagList.contains("-v");
            this.matchEntireLines = flagList.contains("-x");
        }
    }
}