import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class GrepTool {

    public String grep(String text, List<String> flagList, List<String> fileNames) {
        final Flags flags = new Flags(fileNames.size() > 1, flagList);

        return fileNames.parallelStream()
                .flatMap(file -> findInFile(text, file, flags))
                .distinct()
                .collect(Collectors.joining("\n"));
    }

    private Stream<String> findInFile(String text, String fileName, Flags flags) {
        try (Stream<String> lines = Files.lines(Path.of(fileName))) {
            return lines
                    .map(line -> new LineData(line, fileName))
                    .filter(data -> matchLine(text, data.line, flags))
                    .map(data -> getLine(data.fileName, data.line, data.lineNumber++, flags));
        } catch (IOException e) {
            return Stream.empty();
        }
    }

    private boolean matchLine(String text, String line, Flags flags) {
        return flags.invert != lineContainsText(text, line, flags);
    }

    private boolean lineContainsText(String text, String line, Flags flags) {
        return flags.matchEntireLines ? matchWholeLine(text, line, flags) : matchPartOfLine(text, line, flags);
    }

    private boolean matchPartOfLine(String text, String line, Flags flags) {
        return flags.caseInsensitive ? line.toLowerCase().contains(text.toLowerCase()) : line.contains(text);
    }

    private boolean matchWholeLine(String text, String line, Flags flags) {
        return flags.caseInsensitive ? line.equalsIgnoreCase(text) : line.equals(text);
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

    private static class LineData {
        String line;
        String fileName;
        static int lineNumber = 1;

        LineData(String line, String fileName) {
            this.line = line;
            this.fileName = fileName;
        }
    }

    class Flags {

        boolean addFileName;
        boolean addRowNumber;
        boolean containsOneMatchingLine;
        boolean caseInsensitive;
        boolean invert;
        boolean matchEntireLines;

        private Flags(boolean addFileName, List<String> flagList) {
            this.addFileName = addFileName;
            this.addRowNumber = flagList.contains("-n");
            this.containsOneMatchingLine = flagList.contains("-l");
            this.caseInsensitive = flagList.contains("-i");
            this.invert = flagList.contains("-v");
            this.matchEntireLines = flagList.contains("-x");
        }
    }
}