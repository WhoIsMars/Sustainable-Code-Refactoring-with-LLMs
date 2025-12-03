import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class GrepTool {

    public String grep(String text, List<String> flagList, List<String> fileNames) {
        final Flags flags = new Flags(fileNames.size() > 1, flagList);
        StringBuilder result = new StringBuilder();
        boolean first = true;

        for (String file : fileNames) {
            try {
                findInFile(text, file, flags, result, first);
                first = false;
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        return result.toString();
    }

    private void findInFile(String text, String fileName, Flags flags, StringBuilder result, boolean first) throws IOException {
        Path path = Paths.get(fileName);
        try (BufferedReader reader = Files.newBufferedReader(path)) {
            String line;
            int lineNumber = 1;
            Set<String> matchedLines = new HashSet<>(); // Use a Set to ensure distinct lines

            while ((line = reader.readLine()) != null) {
                if (matchLine(text, line, flags)) {
                    String matchedLine = getLine(fileName, line, lineNumber, flags);
                    if (flags.containsOneMatchingLine) {
                        if (first) {
                            result.append(fileName);
                            first = false;
                        }
                        return; // Optimization: Exit early if -l is present
                    }

                    if (matchedLines.add(matchedLine)) { // Add to set and check if it was already present
                        if (result.length() > 0) {
                            result.append("\n");
                        }
                        result.append(matchedLine);
                    }
                }
                lineNumber++;
            }
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