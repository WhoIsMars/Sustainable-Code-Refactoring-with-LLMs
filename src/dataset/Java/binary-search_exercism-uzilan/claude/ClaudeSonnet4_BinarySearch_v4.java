import java.util.List;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final T[] values;
    private final int[] indices;
    private final int size;

    @SuppressWarnings("unchecked")
    public BinarySearch(List<T> list) {
        this.size = list.size();
        this.values = (T[]) new Comparable[size];
        this.indices = new int[size];
        
        for (int i = 0; i < size; i++) {
            this.values[i] = list.get(i);
            this.indices[i] = i;
        }
    }

    public int indexOf(T item) {
        return binarySearchIterative(item, 0, size - 1);
    }

    private int binarySearchIterative(T item, int left, int right) {
        while (left <= right) {
            int middle = left + (right - left) / 2;
            int comparison = item.compareTo(values[middle]);
            
            if (comparison == 0) {
                return indices[middle];
            } else if (comparison < 0) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
        return NOT_FOUND;
    }
}