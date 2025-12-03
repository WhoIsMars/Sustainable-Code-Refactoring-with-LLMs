import java.util.List;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> originalList;

    public BinarySearch(List<T> list) {
        this.originalList = list;
    }

    public int indexOf(T item) {
        return binarySearchIterative(item, 0, originalList.size() - 1);
    }

    private int binarySearchIterative(T item, int left, int right) {
        while (left <= right) {
            int middle = left + (right - left) / 2;
            T middleValue = originalList.get(middle);
            
            int comparison = item.compareTo(middleValue);
            
            if (comparison == 0) {
                return middle;
            } else if (comparison < 0) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
        
        return NOT_FOUND;
    }
}