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
        final String searchText = flags.caseInsensitive ? text.toLowerCase() : text;

        return fileNames.stream()
                .flatMap(file -> findInFile(searchText, file, flags))
                .collect(joining("\n"));
    }

    private Stream<String> findInFile(String searchText, String fileName, Flags flags) {
        try {
            final Path path = Paths.get(fileName);
            return Files.lines(path)
                    .filter(line -> matchLine(searchText, line, flags))
                    .map(line -> getLine(fileName, line, flags))
                    .distinct();
        } catch (IOException e) {
            return Stream.empty();
        }
    }

    private boolean matchLine(String searchText, String line, Flags flags) {
        return flags.invert != lineContainsText(searchText, line, flags);
    }

    private boolean lineContainsText(String searchText, String line, Flags flags) {
        final String processedLine = flags.caseInsensitive ? line.toLowerCase() : line;
        return flags.matchEntireLines ? processedLine.equals(searchText) : processedLine.contains(searchText);
    }

    private String getLine(String fileName, String line, Flags flags) {
        if (flags.containsOneMatchingLine) {
            return fileName;
        }

        if (!flags.addFileName && !flags.addRowNumber) {
            return line;
        }

        final StringBuilder sb = new StringBuilder();
        if (flags.addFileName) {
            sb.append(fileName).append(':');
        }
        if (flags.addRowNumber) {
            sb.append(':');
        }
        sb.append(line);

        return sb.toString();
    }

    static class Flags {
        final boolean addFileName;
        final boolean addRowNumber;
        final boolean containsOneMatchingLine;
        final boolean caseInsensitive;
        final boolean invert;
        final boolean matchEntireLines;

        private Flags(boolean addFileName, List<String> flagList) {
            final Set<String> flagSet = Set.copyOf(flagList);
            this.addFileName = addFileName;
            this.addRowNumber = flagSet.contains("-n");
            this.containsOneMatchingLine = flagSet.contains("-l");
            this.caseInsensitive = flagSet.contains("-i");
            this.invert = flagSet.contains("-v");
            this.matchEntireLines = flagSet.contains("-x");
        }
    }
}