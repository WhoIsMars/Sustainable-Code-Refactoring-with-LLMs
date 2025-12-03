import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Stream;

public class GrepTool {

    public String grep(String text, List<String> flagList, List<String> fileNames) {
        final Flags flags = new Flags(fileNames.size() > 1, flagList);

        return fileNames.stream()
                .flatMap(file -> findInFile(text, file, flags))
                .distinct()
                .collect(java.util.stream.Collectors.joining("\n"));
    }

    private Stream<String> findInFile(String text, String fileName, Flags flags) {
        Path path = Paths.get(fileName);
        try (BufferedReader reader = Files.newBufferedReader(path)) {
            Set<String> matchedLines = new HashSet<>();
            String line;
            int lineNumber = 0;
            while ((line = reader.readLine()) != null) {
                lineNumber++;
                if (matchLine(text, line, flags)) {
                    String formattedLine = getLine(fileName, line, lineNumber, flags);
                    if (flags.containsOneMatchingLine) {
                        if (matchedLines.isEmpty()) {
                            matchedLines.add(fileName);
                            return matchedLines.stream();
                        }
                    } else {
                        matchedLines.add(formattedLine);
                    }
                }
            }
            return matchedLines.stream();

        } catch (IOException e) {
            System.err.println("Error reading file: " + fileName + " - " + e.getMessage());
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

    static class Flags {

        boolean addFileName;
        boolean addRowNumber;
        boolean containsOneMatchingLine;
        boolean caseInsensitiv;
        boolean invert;
        boolean matchEntireLines;

        Flags(boolean addFileName, List<String> flagList) {
            this.addFileName = addFileName;
            this.addRowNumber = flagList.contains("-n");
            this.containsOneMatchingLine = flagList.contains("-l");
            this.caseInsensitiv = flagList.contains("-i");
            this.invert = flagList.contains("-v");
            this.matchEntireLines = flagList.contains("-x");
        }
    }
}