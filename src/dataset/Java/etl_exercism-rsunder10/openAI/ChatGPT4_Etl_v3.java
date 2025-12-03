import java.util.*;

public class Etl {
  public Map<String, Integer> transform(Map<Integer, List<String>> old) {
    Map<String, Integer> newStorage = new HashMap<>(old.size() * 10);
    old.forEach((key, value) -> 
      value.forEach(each -> newStorage.put(each.toLowerCase(Locale.ROOT), key))
    );
    return newStorage;
  }
}