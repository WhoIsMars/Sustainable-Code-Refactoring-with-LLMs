import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Function;
import java.util.function.Predicate;

class ListOps {

    static <T> List<T> append(List<T> list1, List<T> list2) {
        final var list = new ArrayList<>(list1.size() + list2.size());
        list.addAll(list1);
        list.addAll(list2);
        return list;
    }

    static <T> List<T> concat(List<List<T>> listOfLists) {
        if (listOfLists.isEmpty()) {
            return new ArrayList<>();
        }
        
        int totalSize = 0;
        for (List<T> subList : listOfLists) {
            totalSize += subList.size();
        }
        
        final var result = new ArrayList<T>(totalSize);
        for (List<T> subList : listOfLists) {
            result.addAll(subList);
        }
        return result;
    }

    static <T> List<T> filter(List<T> list, Predicate<T> predicate) {
        final var result = new ArrayList<T>();
        for (T item : list) {
            if (predicate.test(item)) {
                result.add(item);
            }
        }
        return result;
    }

    static <T> int size(List<T> list) {
        return list.size();
    }

    static <T, U> List<U> map(List<T> list, Function<T, U> transform) {
        final var result = new ArrayList<U>(list.size());
        for (T item : list) {
            result.add(transform.apply(item));
        }
        return result;
    }

    static <T> List<T> reverse(List<T> list) {
        final var newList = new ArrayList<>(list);
        Collections.reverse(newList);
        return newList;
    }

    static <T, U> U foldLeft(List<T> list, U initial, BiFunction<U, T, U> f) {
        U accumulator = initial;
        for (T item : list) {
            accumulator = f.apply(accumulator, item);
        }
        return accumulator;
    }

    static <T, U> U foldRight(List<T> list, U initial, BiFunction<T, U, U> f) {
        U accumulator = initial;
        for (int i = list.size() - 1; i >= 0; i--) {
            accumulator = f.apply(list.get(i), accumulator);
        }
        return accumulator;
    }

    private ListOps() {
        // No instances.
    }
}