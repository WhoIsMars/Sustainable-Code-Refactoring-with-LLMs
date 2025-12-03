import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> list;

    public BinarySearch(List<T> list) {
        this.list = new ArrayList<>(list);
    }

    public int indexOf(T item) {
        int low = 0;
        int high = list.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent potential overflow
            T midVal = list.get(mid);
            int cmp = midVal.compareTo(item);

            if (cmp < 0) {
                low = mid + 1;
            } else if (cmp > 0) {
                high = mid - 1;
            } else {
                return mid; // Found
            }
        }
        return NOT_FOUND;  // Not found
    }
}