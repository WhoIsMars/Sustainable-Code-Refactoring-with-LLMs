import java.util.HashMap;
import java.util.Map;

public class WordCount {

  public Map<String, Integer> wordCount = new HashMap<>();

  public Map<String, Integer> phrase(String word) {
    word = word.replaceAll("[^A-Za-z0-9]", " ").replaceAll("\\s+", " ");
    String[] words = word.split("\\s");
    
    for(String eachWord : words){
      if (!eachWord.isEmpty()) {
        String lowerWord = eachWord.toLowerCase();
        wordCount.merge(lowerWord, 1, Integer::sum);
      }
    }
    return wordCount;
  }
}