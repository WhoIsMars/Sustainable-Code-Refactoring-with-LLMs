import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> sortedList;

    public BinarySearch(List<T> list) {
        this.sortedList = new ArrayList<>(list);
        Collections.sort(this.sortedList);
    }

    public int indexOf(T item) {
        int low = 0;
        int high = sortedList.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent potential overflow
            T midVal = sortedList.get(mid);
            int cmp = midVal.compareTo(item);

            if (cmp < 0) {
                low = mid + 1;
            } else if (cmp > 0) {
                high = mid - 1;
            } else {
                return findFirstOccurrence(item, mid); // Item found, find first occurrence
            }
        }
        return NOT_FOUND;
    }

    private int findFirstOccurrence(T item, int initialIndex) {
        int index = initialIndex;
        while (index > 0 && sortedList.get(index - 1).equals(item)) {
            index--;
        }
        return index;
    }
}