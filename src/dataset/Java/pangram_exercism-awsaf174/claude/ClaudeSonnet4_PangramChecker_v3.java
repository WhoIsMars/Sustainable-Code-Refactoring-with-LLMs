public class PangramChecker {

  private boolean[] found = new boolean[26];
  private int count = 0;
  
  public boolean isPangram(String input) {
    java.util.Arrays.fill(found, false);
    count = 0;
    
    for (int i = 0; i < input.length() && count < 26; i++) {
      char ch = input.charAt(i);
      if (ch >= 'A' && ch <= 'Z') {
        int index = ch - 'A';
        if (!found[index]) {
          found[index] = true;
          count++;
        }
      } else if (ch >= 'a' && ch <= 'z') {
        int index = ch - 'a';
        if (!found[index]) {
          found[index] = true;
          count++;
        }
      }
    }
    
    return count == 26;
  }
}