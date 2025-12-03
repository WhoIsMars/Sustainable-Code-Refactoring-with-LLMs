import java.util.ArrayList;
import java.util.List;

public class Series {

    private final List<Integer> series;

    public Series(String series) {
        this.series = new ArrayList<>(series.length());
        for (int i = 0; i < series.length(); i++) {
            char c = series.charAt(i);
            if (Character.isDigit(c)) {
                this.series.add(c - '0');
            } else {
                throw new IllegalArgumentException("Input contains non-digit characters!");
            }
        }
    }

    public List<Integer> getDigits() {
        return new ArrayList<>(series); // Return a copy to ensure immutability
    }

    public List<List<Integer>> slices(int number) {
        if (number > series.size() || number <= 0) {
            throw new IllegalArgumentException("Invalid slice size!");
        }
        List<List<Integer>> result = new ArrayList<>(series.size() - number + 1);
        for (int i = 0; i <= series.size() - number; i++) {
            result.add(new ArrayList<>(series.subList(i, i + number)));
        }
        return result;
    }
}