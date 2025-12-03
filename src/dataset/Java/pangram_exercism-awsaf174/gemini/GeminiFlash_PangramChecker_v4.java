public class PangramChecker {

    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }

        boolean[] alphabetPresent = new boolean[26];
        int alphabetCount = 0;

        String lowerCaseInput = input.toLowerCase();

        for (int i = 0; i < lowerCaseInput.length(); i++) {
            char ch = lowerCaseInput.charAt(i);
            if (ch >= 'a' && ch <= 'z') {
                int index = ch - 'a';
                if (!alphabetPresent[index]) {
                    alphabetPresent[index] = true;
                    alphabetCount++;
                    if (alphabetCount == 26) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
}