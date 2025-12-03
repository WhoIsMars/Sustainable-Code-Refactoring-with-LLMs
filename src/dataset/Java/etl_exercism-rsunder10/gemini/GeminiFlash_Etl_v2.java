import java.util.*;

public class Etl {

  public Map<String, Integer> transform(Map<Integer, List<String>> old) {
    Map<String, Integer> newStorage = new HashMap<>();
    for (Map.Entry<Integer, List<String>> entry : old.entrySet()) {
      Integer key = entry.getKey();
      for (String value : entry.getValue()) {
        newStorage.put(value.toLowerCase(), key);
      }
    }
    return newStorage;
  }
}