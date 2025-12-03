import java.util.List;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> list;

    public BinarySearch(List<T> list) {
        this.list = list;
    }

    public int indexOf(T item) {
        return binarySearch(item, 0, list.size() - 1);
    }

    private int binarySearch(T item, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevents potential overflow
            T midVal = list.get(mid);
            int cmp = midVal.compareTo(item);

            if (cmp < 0) {
                low = mid + 1;
            } else if (cmp > 0) {
                high = mid - 1;
            } else {
                return mid; // Item found
            }
        }
        return NOT_FOUND;  // Item not found
    }
}