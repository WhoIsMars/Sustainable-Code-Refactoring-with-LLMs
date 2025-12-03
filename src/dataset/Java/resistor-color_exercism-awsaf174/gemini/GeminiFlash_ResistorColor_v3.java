import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedHashMap;
class ResistorColor {
  private final int[] colorCodes = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  private final String[] colorNames = {"black", "brown", "red", "orange", "yellow", "green", "blue", "violet", "grey", "white"};
  private final HashMap<String, Integer> colorMap = new HashMap<>();

  public ResistorColor() {
    for (int i = 0; i < colorNames.length; i++) {
      colorMap.put(colorNames[i], colorCodes[i]);
    }
  }

    int colorCode(String color) {
      return colorMap.get(color);
    }

    String[] colors() {
        return Arrays.copyOf(colorNames, colorNames.length);
    }
}