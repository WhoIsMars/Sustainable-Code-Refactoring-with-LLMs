public class PangramChecker {

  private int count = 0;
  
    public boolean isPangram(String input) {
        count = 0;
        
        if (input == null || input.length() < 26) {
            return false;
        }
        
        boolean[] found = new boolean[26];
        int uniqueLetters = 0;
        
        for (int i = 0; i < input.length(); i++) {
            char ch = input.charAt(i);
            if (ch >= 'A' && ch <= 'Z') {
                ch = (char)(ch + 32);
            }
            
            if (ch >= 'a' && ch <= 'z') {
                int index = ch - 'a';
                if (!found[index]) {
                    found[index] = true;
                    uniqueLetters++;
                    if (uniqueLetters == 26) {
                        count = 26;
                        return true;
                    }
                }
            }
        }
        
        count = uniqueLetters;
        return false;
    }
}