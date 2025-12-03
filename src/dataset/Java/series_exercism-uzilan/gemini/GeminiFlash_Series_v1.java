import java.util.ArrayList;
import java.util.List;

public class Series {

    private final int[] series;

    public Series(String series) {
        this.series = series.chars().map(Character::getNumericValue).toArray();
    }

    public int[] getDigits() {
        return series;
    }

    public List<List<Integer>> slices(int number) {
        if (number > series.length) {
            throw new IllegalArgumentException("Slice is bigger than series!");
        }

        List<List<Integer>> result = new ArrayList<>();
        for (int i = 0; i <= series.length - number; i++) {
            List<Integer> slice = new ArrayList<>();
            for (int j = 0; j < number; j++) {
                slice.add(series[i + j]);
            }
            result.add(slice);
        }
        return result;
    }
}