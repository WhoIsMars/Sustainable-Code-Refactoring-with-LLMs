import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Set;
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
            Path path = Paths.get(fileName);
            return Files.lines(path)
                    .map(line -> new LineWithNumber(line, 1))
                    .reduce(Stream.<LineWithNumber>empty(),
                            (stream, lineWithNumber) -> {
                                if (matchLine(text, lineWithNumber.line, flags)) {
                                    return Stream.concat(stream, Stream.of(lineWithNumber));
                                }
                                lineWithNumber.number++;
                                return stream;
                            },
                            Stream::concat)
                    .map(lwn -> getLine(fileName, lwn.line, lwn.number, flags))
                    .distinct();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return Stream.empty();
    }

    private Stream<String> findInFile(String text, String fileName, Flags flags) {
        try {
            Path path = Paths.get(fileName);
            final String searchText = flags.caseInsensitiv ? text.toLowerCase() : text;
            
            return Files.lines(path)
                    .map(new LineProcessor(searchText, fileName, flags))
                    .filter(result -> !result.isEmpty())
                    .flatMap(result -> result.stream())
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
        final String processedText = flags.caseInsensitiv ? text.toLowerCase() : text;
        final String processedLine = flags.caseInsensitiv ? line.toLowerCase() : line;
        
        return flags.matchEntireLines ? 
            processedLine.equals(processedText) : 
            processedLine.contains(processedText);
    }

    private String getLine(String fileName, String line, int lineNumber, Flags flags) {
        if (flags.containsOneMatchingLine) {
            return fileName;
        }

        StringBuilder sb = new StringBuilder(fileName.length() + line.length() + 20);
        if (flags.addFileName) {
            sb.append(fileName).append(':');
        }
        if (flags.addRowNumber) {
            sb.append(lineNumber).append(':');
        }
        sb.append(line);

        return sb.toString();
    }

    private static class LineWithNumber {
        final String line;
        int number;

        LineWithNumber(String line, int number) {
            this.line = line;
            this.number = number;
        }
    }

    private class LineProcessor {
        private final String searchText;
        private final String fileName;
        private final Flags flags;
        private int lineNumber = 0;

        LineProcessor(String searchText, String fileName, Flags flags) {
            this.searchText = searchText;
            this.fileName = fileName;
            this.flags = flags;
        }

        Stream<String> apply(String line) {
            lineNumber++;
            final String processedLine = flags.caseInsensitiv ? line.toLowerCase() : line;
            
            boolean matches = flags.matchEntireLines ? 
                processedLine.equals(searchText) : 
                processedLine.contains(searchText);
            
            if (flags.invert) {
                matches = !matches;
            }
            
            return matches ? 
                Stream.of(getLine(fileName, line, lineNumber, flags)) : 
                Stream.empty();
        }
    }

    static class Flags {
        final boolean addFileName;
        final boolean addRowNumber;
        final boolean containsOneMatchingLine;
        final boolean caseInsensitiv;
        final boolean invert;
        final boolean matchEntireLines;

        private Flags(boolean addFileName, List<String> flagList) {
            Set<String> flagSet = Set.copyOf(flagList);
            this.addFileName = addFileName;
            this.addRowNumber = flagSet.contains("-n");
            this.containsOneMatchingLine = flagSet.contains("-l");
            this.caseInsensitiv = flagSet.contains("-i");
            this.invert = flagSet.contains("-v");
            this.matchEntireLines = flagSet.contains("-x");
        }
    }
}