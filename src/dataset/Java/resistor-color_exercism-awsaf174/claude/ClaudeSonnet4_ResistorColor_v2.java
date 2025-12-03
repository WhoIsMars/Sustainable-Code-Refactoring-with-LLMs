import java.util.Arrays;

class ResistorColor {
    private static final String[] COLOR_NAMES = {
        "black", "brown", "red", "orange", "yellow", 
        "green", "blue", "violet", "grey", "white"
    };
    
    int colorCode(String color) {
        for (int i = 0; i < COLOR_NAMES.length; i++) {
            if (COLOR_NAMES[i].equals(color)) {
                return i;
            }
        }
        return -1;
    }

    String[] colors() {
        return Arrays.copyOf(COLOR_NAMES, COLOR_NAMES.length);
    }
}