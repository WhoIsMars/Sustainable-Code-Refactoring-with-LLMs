import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.ArrayList;

public class GrepTool {

    public String grep(String text, List<String> flagList, List<String> fileNames) {
        final Flags flags = new Flags(fileNames.size() > 1, flagList);
        final StringBuilder result = new StringBuilder();
        boolean first = true;

        for (String fileName : fileNames) {
            List<String> matches = findInFile(text, fileName, flags);
            for (String match : matches) {
                if (!first) {
                    result.append('\n');
                }
                result.append(match);
                first = false;
            }
        }

        return result.toString();
    }

    private List<String> findInFile(String text, String fileName, Flags flags) {
        List<String> matches = new ArrayList<>();
        try {
            Path path = Paths.get(fileName);
            List<String> lines = Files.readAllLines(path);
            
            String searchText = flags.caseInsensitiv ? text.toLowerCase() : text;
            
            for (int i = 0; i < lines.size(); i++) {
                String line = lines.get(i);
                if (matchLine(searchText, line, flags)) {
                    String result = getLine(fileName, line, i + 1, flags);
                    if (!matches.contains(result)) {
                        matches.add(result);
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return matches;
    }

    private boolean matchLine(String searchText, String line, Flags flags) {
        return flags.invert != lineContainsText(searchText, line, flags);
    }

    private boolean lineContainsText(String searchText, String line, Flags flags) {
        String processedLine = flags.caseInsensitiv ? line.toLowerCase() : line;
        
        if (flags.matchEntireLines) {
            return processedLine.equals(searchText);
        } else {
            return processedLine.contains(searchText);
        }
    }

    private String getLine(String fileName, String line, int lineNumber, Flags flags) {
        if (flags.containsOneMatchingLine) {
            return fileName;
        }

        StringBuilder sb = new StringBuilder();
        if (flags.addFileName) {
            sb.append(fileName).append(':');
        }
        if (flags.addRowNumber) {
            sb.append(lineNumber).append(':');
        }
        sb.append(line);

        return sb.toString();
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