import java.util.*;

public class Etl {
  private final Map<String, Integer> newStorage = new HashMap<>();

  public Map<String, Integer> transform(Map<Integer, List<String>> old) {
    old.forEach((key, value) ->
        value.forEach(each ->
            newStorage.put(each.toLowerCase(), key)
        )
    );
    return newStorage;
  }
}