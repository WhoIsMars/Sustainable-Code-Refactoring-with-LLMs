import java.util.List;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> sortedList;

    public BinarySearch(List<T> list) {
        this.sortedList = List.copyOf(list); // Ensure immutability and avoid unnecessary wrapping
    }

    public int indexOf(T item) {
        return binarySearch(item, 0, sortedList.size() - 1);
    }

    private int binarySearch(T item, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2; // Avoid potential overflow
            T midValue = sortedList.get(mid);

            int comparison = item.compareTo(midValue);
            if (comparison == 0) {
                return mid;
            } else if (comparison < 0) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return NOT_FOUND;
    }
}