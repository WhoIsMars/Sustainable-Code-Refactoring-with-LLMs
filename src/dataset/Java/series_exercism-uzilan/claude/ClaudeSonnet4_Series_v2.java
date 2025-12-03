import java.util.ArrayList;
import java.util.List;

public class Series {

    private List<Integer> series;

    public Series(String series) {
        this.series = new ArrayList<>(series.length());
        for (int i = 0; i < series.length(); i++) {
            this.series.add(Character.getNumericValue(series.charAt(i)));
        }
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