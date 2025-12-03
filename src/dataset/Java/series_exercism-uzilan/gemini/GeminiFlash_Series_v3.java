import java.util.ArrayList;
import java.util.List;

public class Series {

    private final int[] series;

    public Series(String series) {
        this.series = new int[series.length()];
        for (int i = 0; i < series.length(); i++) {
            this.series[i] = Character.getNumericValue(series.charAt(i));
        }
    }

    public List<Integer> getDigits() {
        List<Integer> digits = new ArrayList<>(series.length);
        for (int digit : series) {
            digits.add(digit);
        }
        return digits;
    }

    public List<List<Integer>> slices(int number) {
        if (number > series.length) {
            throw new IllegalArgumentException("Slice is bigger than series!");
        }

        List<List<Integer>> result = new ArrayList<>(series.length - number + 1);
        for (int i = 0; i <= series.length - number; i++) {
            List<Integer> slice = new ArrayList<>(number);
            for (int j = 0; j < number; j++) {
                slice.add(series[i + j]);
            }
            result.add(slice);
        }
        return result;
    }
}