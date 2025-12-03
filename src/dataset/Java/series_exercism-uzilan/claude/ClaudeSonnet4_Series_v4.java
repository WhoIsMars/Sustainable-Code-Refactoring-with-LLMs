import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Series {

    private final List<Integer> series;

    public Series(String series) {
        int length = series.length();
        List<Integer> digits = new ArrayList<>(length);
        for (int i = 0; i < length; i++) {
            char c = series.charAt(i);
            if (c >= '0' && c <= '9') {
                digits.add(c - '0');
            } else {
                digits.add(Character.getNumericValue(c));
            }
        }
        this.series = Collections.unmodifiableList(digits);
    }

    public List<Integer> getDigits() {
        return series;
    }

    public List<List<Integer>> slices(int number) {
        if (number > series.size()) {
            throw new IllegalArgumentException("Slice is bigger than series!");
        }
        int resultSize = series.size() - number + 1;
        List<List<Integer>> result = new ArrayList<>(resultSize);
        for (int i = 0; i <= series.size() - number; i++) {
            result.add(series.subList(i, i + number));
        }
        return result;
    }
}