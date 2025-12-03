import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class BinarySearch<T extends Comparable<T>> {

    private final int NOT_FOUND = -1;
    private final List<T> sortedList;
    private final List<Integer> originalIndices;

    public BinarySearch(List<T> list) {
        List<T> copy = new ArrayList<>(list);
        this.sortedList = copy;
        this.originalIndices = new ArrayList<>();
        for (int i = 0; i < list.size(); i++) {
            originalIndices.add(i);
        }

        // Sort the list and keep track of original indices
        sortWithOriginalIndices(0, sortedList.size() - 1);
    }

    private void sortWithOriginalIndices(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);

            sortWithOriginalIndices(low, pi - 1);
            sortWithOriginalIndices(pi + 1, high);
        }
    }

    private int partition(int low, int high) {
        T pivot = sortedList.get(high);
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (sortedList.get(j).compareTo(pivot) <= 0) {
                i++;

                // swap sortedList[i] and sortedList[j]
                T temp = sortedList.get(i);
                sortedList.set(i, sortedList.get(j));
                sortedList.set(j, temp);

                // Swap originalIndices[i] and originalIndices[j]
                int tempIndex = originalIndices.get(i);
                originalIndices.set(i, originalIndices.get(j));
                originalIndices.set(j, tempIndex);
            }
        }

        // swap sortedList[i+1] and sortedList[high] (or pivot)
        T temp = sortedList.get(i + 1);
        sortedList.set(i + 1, sortedList.get(high));
        sortedList.set(high, temp);

        // Swap originalIndices[i+1] and originalIndices[high]
        int tempIndex = originalIndices.get(i + 1);
        originalIndices.set(i + 1, originalIndices.get(high));
        originalIndices.set(high, tempIndex);

        return i + 1;
    }


    public int indexOf(T item) {
        int index = binarySearch(item, 0, sortedList.size() - 1);
        if (index == NOT_FOUND) {
            return NOT_FOUND;
        }
        return originalIndices.get(index);
    }

    private int binarySearch(T item, int low, int high) {
        while (low <= high) {
            int mid = low + (high - low) / 2; // Prevent potential overflow
            int comparison = sortedList.get(mid).compareTo(item);

            if (comparison == 0) {
                return mid;
            } else if (comparison < 0) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return NOT_FOUND;
    }
}