import java.util.List;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> sortedList;

    public BinarySearch(List<T> list) {
        this.sortedList = list;
    }

    public int indexOf(T item) {
        return findInSubList(item, sortedList);
    }

    private int findInSubList(T item, List<T> list) {
        int left = 0;
        int right = list.size() - 1;
        
        while (left <= right) {
            int middle = left + (right - left) / 2;
            T middleValue = list.get(middle);
            
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

    private class Node {
        private T value;
        private int index;

        private Node(T value, int index) {
            this.value = value;
            this.index = index;
        }
    }
}