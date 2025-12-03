import java.util.*;

public class Etl {

  public Map<String, Integer> transform(Map<Integer, List<String>> old) {
    int totalSize = old.values().stream().mapToInt(List::size).sum();
    Map<String, Integer> result = new HashMap<>(totalSize);
    
    for (Map.Entry<Integer, List<String>> entry : old.entrySet()) {
      Integer key = entry.getKey();
      List<String> value = entry.getValue();
      for (String each : value) {
        result.put(each.toLowerCase(), key);
      }
    }
    
    return result;
  }
}