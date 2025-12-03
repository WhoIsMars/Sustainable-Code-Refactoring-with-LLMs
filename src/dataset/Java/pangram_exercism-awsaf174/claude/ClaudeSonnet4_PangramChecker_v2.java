public class PangramChecker {
  
    public boolean isPangram(String input) {
        if (input == null || input.length() < 26) {
            return false;
        }
        
        boolean[] seen = new boolean[26];
        int uniqueCount = 0;
        
        for (int i = 0; i < input.length(); i++) {
            char ch = input.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                ch = (char)(ch + 32);
            }
            if (ch >= 'a' && ch <= 'z') {
                int index = ch - 'a';
                if (!seen[index]) {
                    seen[index] = true;
                    uniqueCount++;
                    if (uniqueCount == 26) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }
}