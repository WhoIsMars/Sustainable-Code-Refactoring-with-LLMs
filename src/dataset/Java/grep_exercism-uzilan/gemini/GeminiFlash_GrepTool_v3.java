import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.FileSystems;
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
        Path path = FileSystems.getDefault().getPath(fileName);
        try (BufferedReader reader = Files.newBufferedReader(path)) {
            return reader.lines()
                    .map(line -> new LineWithNumber(line, 0))
                    .map(lwn -> {
                        lwn.lineNumber++;
                        return lwn;
                    })
                    .filter(lwn -> matchLine(text, lwn.line, flags))
                    .map(lwn -> getLine(fileName, lwn.line, lwn.lineNumber, flags))
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
        return flags.matchEntireLines ? matchWholeLine(text, line, flags) : matchPartOfLine(text, line, flags);
    }

    private boolean matchPartOfLine(String text, String line, Flags flags) {
        if (flags.caseInsensitiv) {
            return line.toLowerCase().contains(text.toLowerCase());
        } else {
            return line.contains(text);
        }
    }

    private boolean matchWholeLine(String text, String line, Flags flags) {
        if (flags.caseInsensitiv) {
            return line.equalsIgnoreCase(text);
        } else {
            return line.equals(text);
        }
    }

    private String getLine(String fileName, String line, int lineNumber, Flags flags) {
        if (flags.containsOneMatchingLine) {
            return fileName;
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

    class Flags {

        boolean addFileName;
        boolean addRowNumber;
        boolean containsOneMatchingLine;
        boolean caseInsensitiv;
        boolean invert;
        boolean matchEntireLines;

        private Flags(boolean addFileName, List<String> flagList) {
            this.addFileName = addFileName;
            addRowNumber = flagList.contains("-n");
            containsOneMatchingLine = flagList.contains("-l");
            caseInsensitiv = flagList.contains("-i");
            invert = flagList.contains("-v");
            matchEntireLines = flagList.contains("-x");
        }
    }

    static class LineWithNumber {
        String line;
        int lineNumber;

        public LineWithNumber(String line, int lineNumber) {
            this.line = line;
            this.lineNumber = lineNumber;
        }
    }
}